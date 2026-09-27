#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>

// Average overshoot of the MAX of n iid Normal(0,sigma) draws above 0.
// This equals both: (a) the shading correction c(n), and (b) the average
// naive first-price overpayment, since the winner's bid IS the max draw.
double estimate_shading(int n, double sigma, std::mt19937& rng, int trials) {
    std::normal_distribution<double> noise(0.0, sigma);
    double sum{};
    for (int i = 0; i < trials; i++) {
        double draw = noise(rng);
        double overshoot{draw};
        for (int j = 1; j < n; j++) {
            draw = noise(rng);
            if (draw > overshoot) overshoot = draw;
        }
        sum += overshoot;
    }
    return sum / trials;
}

// Average overshoot of the SECOND-HIGHEST of n iid Normal(0,sigma) draws.
// This is what a second-price winner actually pays (relative to true value).
double estimate_second_price_overpayment(int n, double sigma, std::mt19937& rng, int trials) {
    std::normal_distribution<double> noise(0.0, sigma);
    double sum{};
    for (int i = 0; i < trials; i++) {
        double highest = -1e18, second = -1e18;
        for (int j = 0; j < n; j++) {
            double draw = noise(rng);
            if (draw > highest) {
                second = highest;
                highest = draw;
            } else if (draw > second) {
                second = draw;
            }
        }
        sum += second;
    }
    return sum / trials;
}

int main() {
    int trials{1000000};
    double sigma{10};
    std::mt19937 rng(42);

    std::ofstream file("output/auction_results.csv");
    file << "n,c_n,fp_naive_overpayment,fp_shaded_overpayment,sp_overpayment\n";

    for (int n = 2; n <= 20; n++) {
        double c_n = estimate_shading(n, sigma, rng, trials);
        double fp_naive = estimate_shading(n, sigma, rng, 1000);   // independent smaller sample
        double fp_shaded = fp_naive - c_n;
        double sp = estimate_second_price_overpayment(n, sigma, rng, trials);

        file << n << "," << c_n << "," << fp_naive << "," << fp_shaded << "," << sp << "\n";
    }

    file.close();
    std::cout << "Wrote output/auction_results.csv\n";
    return 0;
}
