#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

int sim(std::mt19937& rng){
    std::uniform_int_distribution<int> die(1, 3);
    int corr{die(rng)};
    if(corr==1){
        return 0;
    } else{return 1;}  
}


int main(){
    std::mt19937 rng(42);
    double sum{};
    for(int i{};i<1000000;i++){
        sum+=sim(rng);
    }
    sum/=1000000;
    std::cout << std::setprecision(10) << sum << std::endl;

}