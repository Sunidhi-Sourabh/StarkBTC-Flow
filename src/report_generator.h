#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <string>
#include "swap_simulator.h"
#include "wallet_verifier.h"

namespace StarkBTC {

    class ReportGenerator {
    public:
        ReportGenerator(const SwapResult& swap, const WalletStatus& wallet);

        std::string generateMarkdown();
        std::string generateHTML();
        std::string generateJSON();
        std::string generateBadge(int score); // ✅ Added to match .cpp

        void saveToFile(const std::string& content, const std::string& format);
        void autoOpenHTML(const std::string& filepath);

    private:
        SwapResult swap_;
        WalletStatus wallet_;
    };

}

#endif // REPORT_GENERATOR_H
