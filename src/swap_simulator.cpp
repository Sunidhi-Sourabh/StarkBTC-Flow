#include "swap_simulator.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace StarkBTC {

    const int CONFIRMATIONS_REQUIRED = 3;

    SwapSimulator::SwapSimulator(double amount, bool debug_mode)
        : amount_(amount), debug_mode_(debug_mode), fee_threshold_(0.0002) {}

    SwapResult SwapSimulator::simulate() {
        double fee = calculateFee(amount_);
        double netAmount = amount_ - fee;

        std::cout << "🔁 Simulating BTC → StarkNet swap...\n";
        std::cout << std::fixed << std::setprecision(8);
        std::cout << "💰 BTC Sent:           " << amount_ << " BTC\n";
        std::cout << "🔸 Estimated Fee:      " << fee << " BTC\n";
        std::cout << "📤 Net Amount:         " << netAmount << " BTC\n";

        simulateConfirmations();

        bool success = fee <= fee_threshold_;
        std::string fallback_reason = success ? "" : "Fee exceeds threshold";

        if (!success && debug_mode_) {
            logFallbackMarkdown(amount_, fee, netAmount);
            logFallbackJSON(amount_, fee, netAmount);
        }

        std::string report = generateReport({success, fee, fallback_reason, ""});
        return {success, fee, fallback_reason, report};
    }

    double SwapSimulator::calculateFee(double amount) {
        return 0.0001 + 0.00005; // Base fee + StarkNet fee
    }

    std::string SwapSimulator::generateReport(const SwapResult& result) {
        std::ostringstream out;
        out << (result.success ? "✅ Swap successful\n" : "❌ Swap failed\n");
        out << "Fee: " << std::fixed << std::setprecision(8) << result.fee << " BTC\n";
        if (!result.fallback_reason.empty()) {
            out << "Fallback Reason: " << result.fallback_reason << "\n";
        }
        return out.str();
    }

    void SwapSimulator::simulateConfirmations() {
        std::cout << "⏳ Waiting for BTC confirmations...\n";
        for (int i = 1; i <= CONFIRMATIONS_REQUIRED; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "✅ Confirmation " << i << "/" << CONFIRMATIONS_REQUIRED << "\n";
        }
    }

    void SwapSimulator::logFallbackMarkdown(double btcAmount, double fee, double netAmount) {
        fs::create_directories("reports");
        std::ofstream md("reports/fallback_log.md");
        if (!md.is_open()) {
            std::cerr << "❌ Failed to write fallback Markdown log.\n";
            return;
        }

        md << "# ⚠️ Fallback Trigger Log\n\n";
        md << "- **BTC Amount:** " << btcAmount << " BTC\n";
        md << "- **Fee:** " << fee << " BTC\n";
        md << "- **Net Amount:** " << netAmount << " BTC\n";
        md << "- **Threshold:** " << fee_threshold_ << " BTC\n";
        md << "- **Status:** Fee exceeds threshold. Suggest batching or alternate L2.\n";

        md.close();
        std::cout << "📝 Fallback log saved to `reports/fallback_log.md`\n";
    }

    void SwapSimulator::logFallbackJSON(double btcAmount, double fee, double netAmount) {
        fs::create_directories("reports");
        json j;
        j["btc_amount"] = btcAmount;
        j["fee"] = fee;
        j["net_amount"] = netAmount;
        j["threshold"] = fee_threshold_;
        j["status"] = "Fee exceeds threshold. Suggest batching or alternate L2.";

        std::ofstream jf("reports/fallback_log.json");
        if (!jf.is_open()) {
            std::cerr << "❌ Failed to write fallback JSON log.\n";
            return;
        }

        jf << std::setw(4) << j << std::endl;
        jf.close();
        std::cout << "🧾 Fallback log saved to `reports/fallback_log.json`\n";
    }

}
