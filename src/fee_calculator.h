#ifndef FEE_CALCULATOR_H
#define FEE_CALCULATOR_H

namespace StarkBTC {

    class FeeCalculator {
    public:
        FeeCalculator(double base_fee, double multiplier);

        double calculate(double amount);
        bool exceedsThreshold(double fee, double threshold);

    private:
        double base_fee_;
        double multiplier_;
    };

}

#endif // FEE_CALCULATOR_H
