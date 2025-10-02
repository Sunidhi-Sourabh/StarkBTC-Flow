#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

// Fee tiers (mock values for simulation)
const double BASE_FEE = 0.0001;       // BTC network fee
const double STARKNET_FEE = 0.00005;  // StarkNet L2 fee
const double FEE_THRESHOLD = 0.0002;  // Trigger fallback if exceeded

void calculateFees(double btcAmount) {
    std::cout << "🧮 Calculating fees for BTC amount: " << btcAmount << " BTC\n";

    double totalFee = BASE_FEE + STARKNET_FEE;
    double netAmount = btcAmount - totalFee;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "🔸 Base Fee (BTC):      " << BASE_FEE << "\n";
    std::cout << "🔸 StarkNet Fee (BTC):  " << STARKNET_FEE << "\n";
    std::cout << "💰 Total Fee:           " << totalFee << " BTC\n";
    std::cout << "📤 Net Amount Sent:     " << netAmount << " BTC\n";

    // Fallback trigger
    if (totalFee > FEE_THRESHOLD) {
        std::cout << "⚠️  Fallback Triggered: Fee exceeds threshold (" << FEE_THRESHOLD << " BTC)\n";
        std::cout << "🔁 Suggest rerouting via alternate L2 or batching swaps.\n";
    } else {
        std::cout << "✅ Fee within acceptable range.\n";
    }
}

