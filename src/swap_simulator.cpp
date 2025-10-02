#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

const double BASE_FEE = 0.0001;
const double STARKNET_FEE = 0.00005;
const double FEE_THRESHOLD = 0.0002;
const int CONFIRMATIONS_REQUIRED = 3;

// Confirmation simulation
void simulateConfirmations() {
    std::cout << "⏳ Waiting for BTC confirmations...\n";
    for (int i = 1; i <= CONFIRMATIONS_REQUIRED; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "✅ Confirmation " << i << "/" << CONFIRMATIONS_REQUIRED << "\n";
    }
}

// Log fallback to Markdown
void logFallbackMarkdown(double btcAmount, double totalFee, double netAmount) {
    fs::create_directories("reports");
    std::ofstream md("reports/fallback_log.md");
    if (!md.is_open()) {
        std::cerr << "❌ Failed to write fallback Markdown log.\n";
        return;
    }

    md << "# ⚠️ Fallback Trigger Log\n\n";
    md << "- **BTC Amount:** " << btcAmount << " BTC\n";
    md << "- **Base Fee:** " << BASE_FEE << " BTC\n";
    md << "- **StarkNet Fee:** " << STARKNET_FEE << " BTC\n";
    md << "- **Total Fee:** " << totalFee << " BTC\n";
    md << "- **Net Amount:** " << netAmount << " BTC\n";
    md << "- **Threshold:** " << FEE_THRESHOLD << " BTC\n";
    md << "- **Status:** Fee exceeds threshold. Suggest batching or alternate L2.\n";

    md.close();
    std::cout << "📝 Fallback log saved to `reports/fallback_log.md`\n";
}

// Log fallback to JSON
void logFallbackJSON(double btcAmount, double totalFee, double netAmount) {
    fs::create_directories("reports");
    json j;
    j["btc_amount"] = btcAmount;
    j["base_fee"] = BASE_FEE;
    j["starknet_fee"] = STARKNET_FEE;
    j["total_fee"] = totalFee;
    j["net_amount"] = netAmount;
    j["threshold"] = FEE_THRESHOLD;
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

// Main swap simulation
void simulateSwap(double btcAmount, bool debugMode) {
    double totalFee = BASE_FEE + STARKNET_FEE;
    double netAmount = btcAmount - totalFee;

    std::cout << "🔁 Simulating BTC → StarkNet swap...\n";
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "💰 BTC Sent:           " << btcAmount << " BTC\n";
    std::cout << "🔸 Base Fee:           " << BASE_FEE << " BTC\n";
    std::cout << "🔸 StarkNet Fee:       " << STARKNET_FEE << " BTC\n";
    std::cout << "📤 Net Amount:         " << netAmount << " BTC\n";

    simulateConfirmations();

    if (totalFee > FEE_THRESHOLD) {
        std::cout << "⚠️  Fallback Triggered: High fee detected.\n";
        if (debugMode) {
            logFallbackMarkdown(btcAmount, totalFee, netAmount);
            logFallbackJSON(btcAmount, totalFee, netAmount);
        }
    } else {
        std::cout << "✅ Swap completed successfully.\n";
    }
}
