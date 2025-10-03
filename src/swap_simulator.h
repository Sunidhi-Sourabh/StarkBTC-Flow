#ifndef SWAP_SIMULATOR_H
#define SWAP_SIMULATOR_H

#include <string>

namespace StarkBTC {

    struct SwapResult {
        bool success;
        double fee;
        std::string fallback_reason;
        std::string report;
    };

    class SwapSimulator {
    public:
        SwapSimulator(double amount, bool debug_mode);

        SwapResult simulate();
        double calculateFee(double amount);
        std::string generateReport(const SwapResult& result);

    private:
        double amount_;
        bool debug_mode_;
        double fee_threshold_;
    };

}

#endif // SWAP_SIMULATOR_H
