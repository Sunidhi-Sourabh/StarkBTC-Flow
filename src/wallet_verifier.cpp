#include "wallet_verifier.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace StarkBTC {

    WalletVerifier::WalletVerifier(const std::string& wallet_address)
        : wallet_address_(wallet_address), score_threshold_(70) {}

    WalletStatus WalletVerifier::verify() {
        int score = calculateScore(wallet_address_);
        bool is_valid = score >= score_threshold_;
        std::string reason = is_valid ? "" : "Score below threshold";

        WalletStatus status = {is_valid, wallet_address_, reason, score};

        logWalletMarkdown(status);
        logWalletJSON(status);

        std::cout << "🔍 Verifying wallet ownership...\n";
        std::cout << "🧠 Wallet ID: " << wallet_address_ << "\n";
        std::cout << "📊 Score: " << score << "\n";
        std::cout << "🔐 Status: " << (is_valid ? "✅ Verified" : "❌ Unverified") << "\n";

        return status;
    }

    int WalletVerifier::calculateScore(const std::string& wallet_address) {
        return wallet_address.length() % 100; // Mock scoring logic
    }

    std::string WalletVerifier::generateBadge(int score) {
        if (score >= 90) return "🏅 Gold";
        if (score >= 70) return "🥈 Silver";
        return "🥉 Bronze";
    }

    void WalletVerifier::logWalletMarkdown(const WalletStatus& status) {
        fs::create_directories("reports");
        std::ofstream md("reports/wallet_verification.md");
        if (!md.is_open()) {
            std::cerr << "❌ Failed to write wallet Markdown log.\n";
            return;
        }

        md << "# 🔐 Wallet Verification Report\n\n";
        md << "- **Wallet ID:** `" << status.address << "`\n";
        md << "- **Score:** " << status.score << "\n";
        md << "- **Status:** " << (status.is_valid ? "✅ Verified" : "❌ Unverified") << "\n";
        md << "- **Badge:** " << generateBadge(status.score) << "\n";
        md << "- **Method:** Mock testnet ping\n";
        md << "- **Notes:** Verification simulated for demo purposes.\n";

        md.close();
        std::cout << "📝 Wallet verification saved to `reports/wallet_verification.md`\n";
    }

    void WalletVerifier::logWalletJSON(const WalletStatus& status) {
        fs::create_directories("reports");
        json j;
        j["wallet_id"] = status.address;
        j["score"] = status.score;
        j["verified"] = status.is_valid;
        j["badge"] = generateBadge(status.score);
        j["method"] = "Mock testnet ping";
        j["notes"] = "Verification simulated for demo purposes";

        std::ofstream jf("reports/wallet_verification.json");
        if (!jf.is_open()) {
            std::cerr << "❌ Failed to write wallet JSON log.\n";
            return;
        }

        jf << std::setw(4) << j << std::endl;
        jf.close();
        std::cout << "🧾 Wallet verification saved to `reports/wallet_verification.json`\n";
    }

}
