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




// #include <iostream>
// #include <array>
// #include <iomanip>
// #include <memory>
// #include <thread>
// #include <vector>
// #include <mutex>
// #include <future>
// #include <chrono>
// #include <ctime>

// template<typename T, size_t S>
// void printMatrix(std::array<std::array<T, S>, S> arr){

//     for(int i=0; i<S; i++){
//         for(int j=0; j<S; j++){
//             std::cout << std::setw(3) << arr[i][j] << ", ";
//         }
//         std::cout << "\n";
//     }
//     std::cout << "----------------------------------------\n";
// }

// //mutex declaration
// std::mutex g_display_mutex;


// template<typename T, size_t S>
// bool calculate_mean(std::shared_ptr<std::array<std::array<T, S>, S>> arrPtr,const std::array<std::array<T, S>, S>& original , int line){
   
//     // std::thread::id this_id = std::this_thread::get_id();
//     // g_display_mutex.lock();
//     // std::cout << "thread " << this_id << " took chunk form " << start << " to " << finish << '\n';
//     // g_display_mutex.unlock();

//     auto maxSize = S;
//     int sum, divider;
//     int maskVerticalStart, maskVerticalStop, maskHorizontalStart, maskHorizontalStop;
//     int j,k,l;
//     // if(line == 0){
//     //     std::this_thread::sleep_for (std::chrono::seconds(5));
//     // }
    
//     for( j= 0; j< maxSize; j++){
//         sum = 0;
//         divider = 0;
//         // where mask strts and ends
//         maskVerticalStart = line - 1;
//         maskVerticalStop = line + 1;
//         maskHorizontalStart = j -1;
//         maskHorizontalStop = j + 1;
//         if(line == 0) maskVerticalStart = line;
//         if(line == maxSize-1) maskVerticalStop = line;
//         if(j == 0) maskHorizontalStart = j;
//         if(j == maxSize-1) maskHorizontalStop = j;

//         divider = (maskVerticalStop - maskVerticalStart + 1) * (maskHorizontalStop - maskHorizontalStart+1);
        
//         for(  k = maskVerticalStart; k <=maskVerticalStop; k++){
//             for(l = maskHorizontalStart; l<=maskHorizontalStop; l++ ){
//                 sum += original[k][l];
//                 // divider++;
//             }
//         }
//         (*arrPtr)[line][j] = sum / divider;
//     }   
    
//     return true;
// }

// template<typename R>
// bool is_ready(std::future<R> const& f){
//     return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; 
// }


// template <typename T, size_t S>
// void boss_thread(std::shared_ptr<std::array<std::array<T, S>, S>> arrPtr,const std::array<std::array<T, S>, S>& original){

//     const int threadNumber = 4s;
//     std::future<bool> allFutures[threadNumber];
//     int lines_passed = 0;
//     int i;
//     clock_t start = clock();

//     for(i=0; i<threadNumber; i++){
//         allFutures[i] = std::async(std::launch::async, calculate_mean<T, S>, arrPtr, original , lines_passed);
//         // std::cout << "task " << i << " took line nr " << lines_passed << '\n';
//         ++lines_passed;
//     }

//     while( lines_passed != S){
//         for(i=0; i<threadNumber; i++){
//             if(lines_passed == S)break;
//             // if( is_ready<bool>(allFutures[i])) {

//             if(allFutures[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready){
//                 allFutures[i].get();
//                 allFutures[i] = std::async(std::launch::async, calculate_mean<T, S>, arrPtr, original , lines_passed);
//                 // std::cout << "task " << i << " took line nr " << lines_passed << '\n';
//                 ++lines_passed;
//             }
//         }
//     }
//     clock_t end = clock();

//     std::cout <<(double) (end-start)/CLOCKS_PER_SEC;
// }



// template<typename T, size_t S>
// void fill_array(std::array<std::array<T, S>, S> *arr){

//     for(int i=0; i<S; i++){
//         for(int j=0; j<S; j++){
//             (*arr)[i][j] = std::rand()%100;
//         }
//     }

// }

// int main(){
//      std::srand(std::time(nullptr));

//     const int arraySize = 1000;



//     std::array<std::array<uint8_t, arraySize>, arraySize> arr;
//     fill_array<uint8_t, arraySize>(&arr);
//     // printMatrix<int, arraySize>(arr);


//     auto arrPtr = std::make_shared< std::array<std::array<uint8_t, arraySize>, arraySize> >();
    
//     // using clock = std::chrono::steady_clock;
//     // clock::time_point start = clock::now();

    
//     clock_t start = clock();
//     std::thread boss(boss_thread<uint8_t, arraySize>,arrPtr, arr );
//     boss.join();
//     clock_t end = clock();
//     // clock::time_point end = clock::now();
    
//     // clock::duration execution_time = end - start;
//     // std::cout <<execution_time.count() << std::endl;;
//     // std::cout <<(double) (end-start)/CLOCKS_PER_SEC;
//     // printMatrix<int, 8>(*arrPtr);

// }