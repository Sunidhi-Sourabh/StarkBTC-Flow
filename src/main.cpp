#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

// Module headers
#include "swap_simulator.h"
#include "wallet_verifier.h"
#include "fee_calculator.h"
#include "report_generator.h"

double btcAmount = 0.005; // Default BTC amount
bool debugMode = false;   // Debug flag

int main(int argc, char* argv[]) {
    std::vector<std::string> flags(argv + 1, argv + argc);

    for (const std::string& flag : flags) {
        if (flag == "--btc-swap") {
            simulateSwap(btcAmount, debugMode);
        }
        else if (flag == "--verify-wallet") {
            verifyWalletOwnership();
        }
        else if (flag == "--score") {
            calculateFees(btcAmount);
        }
        else if (flag.rfind("--report-format=", 0) == 0) {
            std::string format = flag.substr(16);
            if (!format.empty()) {
                generateReportByFormat(format);
            } else {
                std::cerr << "❌ Missing format. Use: --report-format=md|html|json|all\n";
            }
        }
        else if (flag.rfind("--amount=", 0) == 0) {
            try {
                btcAmount = std::stod(flag.substr(9));
                std::cout << "🔢 BTC amount set to: " << btcAmount << " BTC\n";
            } catch (...) {
                std::cerr << "❌ Invalid BTC amount format.\n";
            }
        }
        else if (flag == "--simulate-swap") {
            simulateSwap(btcAmount, debugMode);
        }
        else if (flag == "--open") {
#ifdef _WIN32
            system("start reports\\swap_report.html");
#elif __APPLE__
            system("open reports/swap_report.html");
#else
            system("xdg-open reports/swap_report.html");
#endif
        }
        else if (flag == "--debug") {
            debugMode = true;
            std::cout << "🛠 Debug mode enabled: fallback trace logs will be generated.\n";
        }
        else {
            std::cerr << "⚠️  Unknown flag: " << flag << "\n";
        }
    }

    if (flags.empty()) {
        std::cout << "📦 StarkBTC Flow CLI\n";
        std::cout << "Usage:\n";
        std::cout << "  --btc-swap               Simulate BTC → StarkNet swap\n";
        std::cout << "  --verify-wallet          Validate wallet ownership\n";
        std::cout << "  --score                  Calculate fees and fallback triggers\n";
        std::cout << "  --report-format=md       Generate Markdown report\n";
        std::cout << "  --report-format=html     Generate HTML report\n";
        std::cout << "  --report-format=json     Generate JSON report\n";
        std::cout << "  --report-format=all      Generate all formats\n";
        std::cout << "  --simulate-swap          Run full swap simulation with fallback logs\n";
        std::cout << "  --amount=0.01            Set custom BTC amount\n";
        std::cout << "  --open                   Launch dashboard preview (HTML report)\n";
        std::cout << "  --debug                  Enable fallback trace logs\n";
    }

    return 0;
}

