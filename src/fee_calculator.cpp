#include "fee_calculator.h"
#include <iostream>
#include <iomanip>

namespace StarkBTC {

    FeeCalculator::FeeCalculator(double base_fee, double multiplier)
        : base_fee_(base_fee), multiplier_(multiplier) {}

    double FeeCalculator::calculate(double amount) {
        double starknet_fee = base_fee_ * 0.5; // Mock L2 fee logic
        double total_fee = base_fee_ + starknet_fee + amount * multiplier_;
        double net_amount = amount - total_fee;

        std::cout << std::fixed << std::setprecision(8);
        std::cout << "🧮 Calculating fees for BTC amount: " << amount << " BTC\n";
        std::cout << "🔸 Base Fee (BTC):      " << base_fee_ << "\n";
        std::cout << "🔸 StarkNet Fee (BTC):  " << starknet_fee << "\n";
        std::cout << "🔸 Multiplier Fee:      " << amount * multiplier_ << "\n";
        std::cout << "💰 Total Fee:           " << total_fee << " BTC\n";
        std::cout << "📤 Net Amount Sent:     " << net_amount << " BTC\n";

        return total_fee;
    }

    bool FeeCalculator::exceedsThreshold(double fee, double threshold) {
        if (fee > threshold) {
            std::cout << "⚠️  Fallback Triggered: Fee exceeds threshold (" << threshold << " BTC)\n";
            std::cout << "🔁 Suggest rerouting via alternate L2 or batching swaps.\n";
            return true;
        } else {
            std::cout << "✅ Fee within acceptable range.\n";
            return false;
        }
    }

}
