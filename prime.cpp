#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>
#include <array>
//--------------------------------------------------------
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
//--------------------------------------------------------
int power(int x, unsigned int y, int p){
    int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

bool miller_rabin(int number, int d){

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(2, number-2);

    int random_number = dis(gen);

    // int x = (int)std::pow(random_number, d) % number;
    int x = power(random_number, d, number);

    if(x == 1 || x == (number - 1) )return true;
    
    while(d != number-1){
        x = (x*x) %number;
        d *= 2;
        if (x == 1) return false;
        if (x == number-1) return true;
    }


    return false;
}

bool isPrime_miller_rabin(int number){
    int d = number - 1;
    while(d % 2 == 0) d /= 2;


    for (int i = 0; i < 4; i++){
        if(miller_rabin( number,  d) == false) return false;
    }


    return true;
}

//--------------------------------------------------------



int main(){
    std::srand(std::time(nullptr));
    long number = 998;

// std::cout << "number " << number << " res: " << trial_division(number) <<std::endl;
    std::array<int, 42> arr = {233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, };

  int i = 0;
    for(auto elem: arr){

        if( isPrime_miller_rabin(elem) != true){
            std::cout << elem << std::endl;
            i++;
        }
                

    }
  std::cout << i << std::endl;

}