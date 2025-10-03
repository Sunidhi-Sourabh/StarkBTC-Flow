#ifndef WALLET_VERIFIER_H
#define WALLET_VERIFIER_H

#include <string>

namespace StarkBTC {

    struct WalletStatus {
        bool is_valid;
        std::string address;
        std::string reason;
        int score;
    };

    class WalletVerifier {
    public:
        WalletVerifier(const std::string& wallet_address);

        WalletStatus verify();
        int calculateScore(const std::string& wallet_address);
        std::string generateBadge(int score);

        void logWalletMarkdown(const WalletStatus& status); // ✅ Declare this
        void logWalletJSON(const WalletStatus& status);     // ✅ Declare this

    private:
        std::string wallet_address_;
        int score_threshold_;
    };

}

#endif // WALLET_VERIFIER_H
