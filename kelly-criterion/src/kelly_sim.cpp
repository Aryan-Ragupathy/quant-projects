#include <iostream>
#include <random>
#include <fstream>


void simulate_path(double f, std::mt19937& rng,double(&arr)[600][401],int iter) {
    double wealth{1};
    arr[iter][0] = wealth;
    std::bernoulli_distribution coin(0.55);
    for(int i{1};i<=400;i++){
        if(coin(rng)){wealth*=(1+f);}
        else{wealth*=(1-f);}
        arr[iter][i] = wealth;
    }
    return ;
}


int main() {
    std::mt19937 rng(42);
    double arr1[600][401];
    double arr2[600][401];
    double arr3[600][401];
    double arr4[600][401];


    for(int i{};i<600;i++){
        simulate_path(.05,rng,arr1,i);
    }
    for(int i{};i<600;i++){
        simulate_path(.1,rng,arr2,i);
    }
    for(int i{};i<600;i++){
        simulate_path(.2,rng,arr3,i);
    }
    for(int i{};i<600;i++){
        simulate_path(.3,rng,arr4,i);
    }



    std::ofstream file1("path005.csv");

    for (int j{}; j < 600; j++) {
        for (int i{}; i < 401; i++) {
            file1 << arr1[j][i] ;
            if(i!=400){file1<<",";}
        }
        file1 << "\n";
    }

    file1.close();

    std::ofstream file2("path010.csv");

    for (int j{}; j < 600; j++) {
        for (int i{}; i < 401; i++) {
            file2 << arr2[j][i] ;
            if(i!=400){file2<<",";}
        }
        file2 << "\n";
    }

    file2.close();

    std::ofstream file3("path020.csv");

    for (int j{}; j < 600; j++) {
        for (int i{}; i < 401; i++) {
            file3 << arr3[j][i] ;
            if(i!=400){file3<<",";}
        }
        file3 << "\n";
    }

    file3.close();

    std::ofstream file4("path030.csv");

    for (int j{}; j < 600; j++) {
        for (int i{}; i < 401; i++) {
            file4 << arr4[j][i] ;
            if(i!=400){file4<<",";}
        }
        file4 << "\n";
    }

    file4.close();


}