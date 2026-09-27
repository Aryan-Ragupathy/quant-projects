#include <iostream>
#include <random>
#include <fstream>
#include <cmath>


double N(double x) {
    return 0.5 * (1 + std::erf(x / std::sqrt(2.0)));
}

double sim(double s0,double k,double r,double sigma,double t,std::mt19937& rng,int trials){
    std::normal_distribution<double> norm(0.0, 1);
    double sum{};
    double payoff{};
    for(int i{};i<trials;i++){
        double z = norm(rng);
        double st = s0 * std::exp((r - sigma*sigma/2.0)*t + sigma*std::sqrt(t)*z);
        payoff = (0>(st-k)?0:(st-k));
        sum+=payoff;
    }
    sum=sum/trials;
    sum=sum/std::exp(r*t);
    return sum;
}

double black_scholes(double s0,double k,double r,double sigma,double t){
    double d1=(std::log(s0/k)+r*t+sigma*sigma*t/2)/(sigma*sqrt(t));
    double d2 = d1 - sigma*sqrt(t);
    double call_price=s0*N(d1)-k*N(d2)/std::exp(r*t);
    return call_price;
}

int main(){
    std::mt19937 rng(42);
    double s0{100},k{100},r{.05},sigma{.2},t{1};
    int n_points = 100;
    double trial_counts[100];
    double log_start = std::log10(100.0);      // log10(100) = 2
    double log_end = std::log10(1000000.0);    // log10(1,000,000) = 6

    for (int i = 0; i < n_points; i++) {
        double exponent = log_start + (log_end - log_start) * i / (n_points - 1);
        trial_counts[i] = std::round(std::pow(10.0, exponent));
    }

    double bs_price = black_scholes(s0, k, r, sigma, t); 


    std::ofstream file("output.csv");
    file << "trials,mc_price,black_scholes_price\n";

    for (int i = 0; i < n_points; i++) {
        double mc_price = sim(s0, k, r, sigma, t, rng, trial_counts[i]);
        file << trial_counts[i] << "," << mc_price << "," << bs_price << "\n";
    }


}