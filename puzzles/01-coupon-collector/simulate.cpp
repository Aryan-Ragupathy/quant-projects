#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

int sim(std::mt19937& rng){
    std::uniform_int_distribution<int> die(1, 6);
    bool seen[6] = {false};
    int turns{};
    while(!(seen[0]&&seen[1]&&seen[2]&&seen[3]&&seen[4]&&seen[5])){
        int roll = die(rng);
        seen[roll-1] = true;
        turns++;
    }
    return turns;
}


int main() {
    std::mt19937 rng(42);
    double sum{};
    for(int i{};i<1000000;i++){
        sum+=sim(rng);
    }
    sum=sum/1000000;
    std::cout << std::setprecision(10) << sum << std::endl;
    
}