#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>
#include <array>
#include <future>
#include <chrono>
#include <ctime>
#include <mutex>
#include <set>
#include <thread>
#include <iomanip>
#include <memory>

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


// std::pair<long,bool> check_prime_thread(std::future<std::pair<long,bool>> &f, long number){
std::pair<long,bool> check_prime_thread(long number){

    std::pair<long,bool> res(number, trial_division(number));

    return res;
}


int main(){
    std::srand(std::time(nullptr)); //dem random numbers
    int cnt = 0;
    int NUMBER_OF_THEADS = 4;
    std::set<long> prime_numbers;
    std::set<long> not_prime_numbers;

    std::future<std::pair<long,bool>> allFutures[NUMBER_OF_THEADS];


    std::vector<long> arr = { 16, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, };
    auto vec_size = arr.size();
    
    for(int i=0; i<NUMBER_OF_THEADS; i++){
        allFutures[i] = std::async(std::launch::async, check_prime_thread, arr.back());
        arr.pop_back();
        cnt++;
        
    }
    std::mutex _lock;
    
    // while (!arr.empty() && (vec_size != cnt)){
    while ( prime_numbers.size() + not_prime_numbers.size()!=vec_size ){
        for(int i=0; i < NUMBER_OF_THEADS; i++){
            try{
                if(allFutures[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready){
                    _lock.lock();
                    auto r = allFutures[i].get();
                    if(r.second)
                        prime_numbers.insert(r.first);
                    else
                        not_prime_numbers.insert(r.first);

                    if(!arr.empty()){
                        allFutures[i] = std::async(std::launch::async, check_prime_thread, arr.back());
                        arr.pop_back();
                        cnt++;
                    }
                    _lock.unlock();
                }
            }catch(const std::future_error& e){
                //why bother
            }
        }
    }

    
    std::cout<< "number of all elements: " <<vec_size << std::endl;
    std::cout<< "number of cnt elements: " <<cnt << std::endl;
    std::cout << "number of prime numbers in set: " << prime_numbers.size() << std::endl;
    std::cout << "number of regural numbers in set: " << not_prime_numbers.size() << std::endl;

}

