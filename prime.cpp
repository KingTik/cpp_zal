#include <iostream>



bool trial_division(long number){
    if(number <= 1)
        return false;
    if(number <= 3)
        return true;

    if(number % 2 == 0 || number % 3 == 0)
        return false;
    
    int i = 5;

    while(i*i <= number){
        if(number % i == 0 || number % (i+2) == 0){
            return false;
        } 
        i = i+6;
    }

    return true;
}







int main(){

long number = 998;

std::cout << "number " << number << " res: " << trial_division(number) <<std::endl;



}