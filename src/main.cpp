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

using namespace StarkBTC;

double btcAmount = 0.005; // Default BTC amount
bool debugMode = false;   // Debug flag
std::string walletAddress = "user_wallet_xyz"; // Default wallet

int main(int argc, char* argv[]) {
    std::vector<std::string> flags(argv + 1, argv + argc);

    SwapResult swap;
    WalletStatus wallet;
    bool swapDone = false;
    bool walletChecked = false;

    for (const std::string& flag : flags) {
        if (flag == "--btc-swap" || flag == "--simulate-swap") {
            SwapSimulator simulator(btcAmount, debugMode);
            swap = simulator.simulate();
            swapDone = true;
        }
        else if (flag == "--verify-wallet") {
            WalletVerifier verifier(walletAddress);
            wallet = verifier.verify();
            walletChecked = true;
        }
        else if (flag == "--score") {
            FeeCalculator feeCalc(0.0001, 1.5);
            double fee = feeCalc.calculate(btcAmount);
            std::cout << "💰 Estimated fee: " << fee << " BTC\n";
            if (feeCalc.exceedsThreshold(fee, 0.001)) {
                std::cout << "⚠️ Fee exceeds threshold. Fallback logic may be triggered.\n";
            }
        }
        else if (flag.rfind("--report-format=", 0) == 0) {
            std::string format = flag.substr(16);
            if (!format.empty()) {
                if (!swapDone) {
                    SwapSimulator simulator(btcAmount, debugMode);
                    swap = simulator.simulate();
                }
                if (!walletChecked) {
                    WalletVerifier verifier(walletAddress);
                    wallet = verifier.verify();
                }

                ReportGenerator reportGen(swap, wallet);
                if (format == "md") {
                    reportGen.saveToFile(reportGen.generateMarkdown(), "md");
                } else if (format == "html") {
                    reportGen.saveToFile(reportGen.generateHTML(), "html");
                } else if (format == "json") {
                    reportGen.saveToFile(reportGen.generateJSON(), "json");
                } else if (format == "all") {
                    reportGen.saveToFile(reportGen.generateMarkdown(), "md");
                    reportGen.saveToFile(reportGen.generateHTML(), "html");
                    reportGen.saveToFile(reportGen.generateJSON(), "json");
                } else {
                    std::cerr << "❌ Unknown format. Use: md | html | json | all\n";
                }
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
            std::cerr << "⚠️ Unknown flag: " << flag << "\n";
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
