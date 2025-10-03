#include "report_generator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <ctime>
#include <cstdlib>
#include <nlohmann/json.hpp> // Requires JSON library

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace StarkBTC {

    ReportGenerator::ReportGenerator(const SwapResult& swap, const WalletStatus& wallet)
        : swap_(swap), wallet_(wallet) {}

    std::string getTimestamp() {
        std::time_t now = std::time(nullptr);
        char buf[100];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(buf);
    }

    std::string ReportGenerator::generateMarkdown() {
        std::ostringstream report;
        report << "# 📊 StarkBTC Flow Swap Report\n\n";
        report << "**Timestamp:** " << getTimestamp() << "\n";
        report << "**Wallet ID:** `" << wallet_.address << "`\n";
        report << "**Swap Status:** " << (swap_.success ? "✅ Success" : "❌ Failed") << "\n\n";

        report << "## 🔐 Trust Badge\n";
        report << "**Score:** " << wallet_.score << "\n";
        report << "**Badge:** " << generateBadge(wallet_.score) << "\n\n";

        report << "## 🔁 Swap Summary\n";
        report << "- **Fee:** " << std::fixed << std::setprecision(8) << swap_.fee << " BTC\n";
        report << "- **Fallback Reason:** " << (swap_.fallback_reason.empty() ? "None" : swap_.fallback_reason) << "\n\n";

        report << "## 🧠 Notes\n";
        report << "- Wallet verified via mock testnet.\n";
        report << "- Report generated for demo purposes.\n";

        return report.str();
    }

    std::string ReportGenerator::generateHTML() {
        std::ostringstream html;
        html << "<!DOCTYPE html><html><head><title>StarkBTC Flow Report</title></head><body style='font-family:sans-serif;'>\n";
        html << "<h1>📊 StarkBTC Flow Swap Report</h1>\n";
        html << "<p><strong>Timestamp:</strong> " << getTimestamp() << "<br>\n";
        html << "<strong>Wallet ID:</strong> " << wallet_.address << "<br>\n";
        html << "<strong>Swap Status:</strong> " << (swap_.success ? "✅ Success" : "❌ Failed") << "</p>\n";

        html << "<h2>🔐 Trust Badge</h2>\n<p>Score: <strong>" << wallet_.score << "</strong><br>Badge: <strong>" << generateBadge(wallet_.score) << "</strong></p>\n";

        html << "<h2>🔁 Swap Summary</h2>\n<ul>\n";
        html << "<li>Fee: " << swap_.fee << " BTC</li>\n";
        html << "<li>Fallback Reason: " << (swap_.fallback_reason.empty() ? "None" : swap_.fallback_reason) << "</li>\n</ul>\n";

        html << "<h2>🧠 Notes</h2>\n<ul>\n";
        html << "<li>Wallet verified via mock testnet.</li>\n";
        html << "<li>Report generated for demo purposes.</li>\n</ul>\n";

        html << "</body></html>";
        return html.str();
    }

    std::string ReportGenerator
