#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <filesystem>
#include <ctime>
#include <cstdlib>
#include <nlohmann/json.hpp> // Requires JSON library

using json = nlohmann::json;
namespace fs = std::filesystem;

// Mock data
const std::string BADGE = "✅ Trusted";
const double BTC_AMOUNT = 0.005;
const double BASE_FEE = 0.0001;
const double STARKNET_FEE = 0.00005;
const double TOTAL_FEE = BASE_FEE + STARKNET_FEE;
const double NET_AMOUNT = BTC_AMOUNT - TOTAL_FEE;
const std::string WALLET_ID = "mock_wallet_123";
const std::string SWAP_ID = "swap_456_xyz";

// Timestamp generator
std::string getTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

// Markdown report
void generateMarkdownReport() {
    fs::create_directories("reports");
    std::ofstream report("reports/swap_report.md");
    if (!report.is_open()) {
        std::cerr << "❌ Failed to create Markdown report.\n";
        return;
    }

    report << "# 📊 StarkBTC Flow Swap Report\n\n";
    report << "**Timestamp:** " << getTimestamp() << "\n";
    report << "**Wallet ID:** `" << WALLET_ID << "`\n";
    report << "**Swap ID:** `" << SWAP_ID << "`\n\n";

    report << "## 🔐 Trust Badge\n";
    report << "**Status:** " << BADGE << "\n\n";

    report << "## 🔁 Swap Summary\n";
    report << "- **BTC Sent:** " << std::fixed << std::setprecision(8) << BTC_AMOUNT << " BTC\n";
    report << "- **Base Fee:** " << BASE_FEE << " BTC\n";
    report << "- **StarkNet Fee:** " << STARKNET_FEE << " BTC\n";
    report << "- **Total Fee:** " << TOTAL_FEE << " BTC\n";
    report << "- **Net Amount Received:** " << NET_AMOUNT << " BTC\n\n";

    report << "## 🧠 Notes\n";
    report << "- Fallback logic not triggered.\n";
    report << "- Wallet verified via mock testnet.\n";
    report << "- Report generated for demo purposes.\n";

    report.close();
    std::cout << "📄 Markdown report saved to `reports/swap_report.md`\n";
}

// HTML report
void generateHTMLReport() {
    fs::create_directories("reports");
    std::ofstream html("reports/swap_report.html");
    if (!html.is_open()) {
        std::cerr << "❌ Failed to create HTML report.\n";
        return;
    }

    html << "<!DOCTYPE html><html><head><title>StarkBTC Flow Report</title></head><body style='font-family:sans-serif;'>\n";
    html << "<h1>📊 StarkBTC Flow Swap Report</h1>\n";
    html << "<p><strong>Timestamp:</strong> " << getTimestamp() << "<br>\n";
    html << "<strong>Wallet ID:</strong> " << WALLET_ID << "<br>\n";
    html << "<strong>Swap ID:</strong> " << SWAP_ID << "</p>\n";

    html << "<h2>🔐 Trust Badge</h2>\n<p>Status: <strong>" << BADGE << "</strong></p>\n";

    html << "<h2>🔁 Swap Summary</h2>\n<ul>\n";
    html << "<li>BTC Sent: " << BTC_AMOUNT << " BTC</li>\n";
    html << "<li>Base Fee: " << BASE_FEE << " BTC</li>\n";
    html << "<li>StarkNet Fee: " << STARKNET_FEE << " BTC</li>\n";
    html << "<li>Total Fee: " << TOTAL_FEE << " BTC</li>\n";
    html << "<li>Net Amount Received: " << NET_AMOUNT << " BTC</li>\n</ul>\n";

    html << "<h2>🧠 Notes</h2>\n<ul>\n";
    html << "<li>Fallback logic not triggered.</li>\n";
    html << "<li>Wallet verified via mock testnet.</li>\n";
    html << "<li>Report generated for demo purposes.</li>\n</ul>\n";

    html << "</body></html>";
    html.close();
    std::cout << "🌐 HTML report saved to `reports/swap_report.html`\n";

    // Auto-open in browser
#ifdef _WIN32
    system("start reports\\swap_report.html");
#elif __APPLE__
    system("open reports/swap_report.html");
#else
    system("xdg-open reports/swap_report.html");
#endif
}

// JSON report
void generateJSONReport() {
    fs::create_directories("reports");
    json j;
    j["timestamp"] = getTimestamp();
    j["wallet_id"] = WALLET_ID;
    j["swap_id"] = SWAP_ID;
    j["trust_badge"] = BADGE;
    j["btc_sent"] = BTC_AMOUNT;
    j["base_fee"] = BASE_FEE;
    j["starknet_fee"] = STARKNET_FEE;
    j["total_fee"] = TOTAL_FEE;
    j["net_amount"] = NET_AMOUNT;
    j["notes"] = {
        "Fallback logic not triggered",
        "Wallet verified via mock testnet",
        "Report generated for demo purposes"
    };

    std::ofstream jsonFile("reports/swap_report.json");
    if (!jsonFile.is_open()) {
        std::cerr << "❌ Failed to create JSON report.\n";
        return;
    }

    jsonFile << std::setw(4) << j << std::endl;
    jsonFile.close();
    std::cout << "🧾 JSON report saved to `reports/swap_report.json`\n";
}

// CLI flag handler
void generateReportByFormat(const std::string& format) {
    if (format == "md") generateMarkdownReport();
    else if (format == "html") generateHTMLReport();
    else if (format == "json") generateJSONReport();
    else if (format == "all") {
        generateMarkdownReport();
        generateHTMLReport();
        generateJSONReport();
    } else {
        std::cerr << "❌ Unknown format: " << format << "\n";
        std::cerr << "Usage: --report-format [md|html|json|all]\n";
    }
}

