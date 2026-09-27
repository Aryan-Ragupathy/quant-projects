#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

int noOfPeople(std::mt19937& rng,bool (&arr) [365]){
    std::uniform_int_distribution<int> ran(1, 365);
    int people{};
    while(true){
        int date = ran(rng);
        people++;
        if(arr[date-1]){return people;}
        else{arr[date-1]= true;}
    }
}



int main(){
    std::mt19937 rng(42);
    bool arr[365] = {false};
    double sum{};
    for(int i{};i<100000;i++){
        sum+=noOfPeople(rng,arr);
        for(int j{};j<365;j++){arr[j]=false;}
    }
    sum=sum/100000;
    std::cout << std::setprecision(10) << sum  << std::endl; 


    double term{1};
    double act{};
    for(int i{1};i<365;i++){
        act+=term*i*(i+1)/365;
        term=term*(365-i)/365;
    }
    std::cout << std::setprecision(10) << act  << std::endl;



}