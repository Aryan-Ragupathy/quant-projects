#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

int sim(std::mt19937& rng,int n,int i, double p){
    std::bernoulli_distribution win(p);
    while(true){
        if(win(rng)){i++;}
        else{i--;}
        if(i==n){return 1;}
        else if(i==0){return 0;}
    }
}

int main(){
    std::mt19937 rng(42);
    double sum{};
    int n{},i{};
    double p{};
    std::cin >> n >> i >> p;
    for(int j{};j<1000000;j++){
        sum+= sim(rng,n,i,p);
   }
    sum = sum/1000000;
    std::cout << std::setprecision(10) << sum << std::endl;   

}