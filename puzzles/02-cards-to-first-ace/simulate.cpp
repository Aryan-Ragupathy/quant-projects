#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

int sim(std::mt19937& rng,int (&arr) [52]){
    std::shuffle(arr,arr+52,rng);
    int pos{};
    for(int i{};i<52;i++){
        if(arr[i]<4){
            pos=i+1;
            break;
        }
    }
    return pos;

}


int main() {
    std::mt19937 rng(42);
    double sum{};
    int arr[52];
    for(int i{};i<52;i++){
        arr[i]=i;
    }
    for(int i{};i<1000000;i++){
        sum+=sim(rng,arr);
    }
    sum=sum/1000000;
    std::cout << std::setprecision(10) << sum << std::endl;   
}