#include <iostream>

int main(){

    int iterations = 60;
    double rate = 0.01;
    double yearly = 4200.0;
    double value = 3000.0;

    for (int i = 0; i < iterations; i++){
        value += yearly;
        value += value*rate;
        std::cout << "Value is $" << value << "\n";
    }
    
    

}