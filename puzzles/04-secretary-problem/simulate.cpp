#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

int sim(std::mt19937& rng,int (&arr) [1000]){
    std::shuffle(arr,arr+1000,rng);
    int max{};
    for(int i{};i<=366;i++){
        if(arr[i]>max){max=arr[i];}
    }
    for(int i{367};i<=998;i++){
        if(arr[i]>max){
            if(arr[i]==1000){return 1;}
            else{return 0;}
        }
    }
    if(arr[999]==1000){return 1;}
    else{return 0;}
}


int main(){
    std::mt19937 rng(42);
    double sum{};
    int arr[1000];
    for(int i{1};i<=1000;i++){arr[i-1]=i;}
    for(int i{};i<100000;i++){
        sum+=sim(rng,arr);
    }
    sum = sum/100000;
    std::cout << std::setprecision(10) << sum  << std::endl; 

}