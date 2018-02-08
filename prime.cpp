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
#include <iterator>
#include <fstream>
#include <algorithm> // WINCYJ INKLUDUF

class GenerateData{

    std::string filePath = "data.txt";
    std::ofstream file;
public:
    void generate_to_file(const int &howManyNumbers){
        file.open(this->filePath); 
        long i = 1;

        std::ostream_iterator<long> out_it (file," ");
        std::generate_n(out_it, howManyNumbers, [&i]()mutable{return i++;});

        file.close();
    }

    std::vector<long> read_from_file(const int &generateHowMany){

        std::vector<long> data;
        std::ifstream file_temp(this->filePath);
        std::istream_iterator<long> in_it (file_temp);
        
        std::generate_n(std::back_inserter(data), generateHowMany, [&in_it](){
            
            
            auto reading = *in_it;
            
            ++in_it;
            return reading;

        }); 

        file_temp.close();

        return data;
    }

};




class PrimeCheckerIF{
    public:
    virtual std::pair<long,bool> check_prime_thread(long) = 0;
    virtual std::string name() = 0;
};


class TrialDivision: public PrimeCheckerIF{
    bool trial_division(long number){
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
    public:

    virtual std::pair<long,bool> check_prime_thread(long number){

        std::pair<long,bool> res(number, trial_division(number));
        return res;
    }

    virtual std::string name(){return "Trial Division";} 
};


class MillerRabin: public PrimeCheckerIF{
    // source https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/
    int power(int x, unsigned int y, int p)
    {
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

    bool miillerTest(int d, int n)
    {

        int a = 2 + rand() % (n - 4);
    
        int x = power(a, d, n);
    
        if (x == 1  || x == n-1)
        return true;
    

        while (d != n-1)
        {
            x = (x * x) % n;
            d *= 2;
    
            if (x == 1)      return false;
            if (x == n-1)    return true;
        }
    
        // Return composite
        return false;
    }

    bool isPrime(int n, int k = 4)
    {
        // Corner cases
        if (n <= 1 || n == 4)  return false;
        if (n <= 3) return true;
    
        // Find r such that n = 2^d * r + 1 for some r >= 1
        int d = n - 1;
        while (d % 2 == 0)
            d /= 2;
    
        // Iterate given nber of 'k' times
        for (int i = 0; i < k; i++)
            if (miillerTest(d, n) == false)
                return false;
    
        return true;
    }
    public:
    virtual std::pair<long,bool> check_prime_thread(long number){

        std::pair<long,bool> res(number, isPrime(number));
        return res;
    }
    virtual std::string name(){return "Miller-Rabin";}
};





int main(){

    GenerateData generator1;
    // generator1.generate_to_file(10000);

    int DataSetSize = 10000;
    std::vector<long> vec = generator1.read_from_file(DataSetSize);
    std::srand(std::time(nullptr)); //dem random numbers
    int cnt = 0;
    int NUMBER_OF_THEADS = 4; // <--- NUMBER OF THREADS
    std::set<long> prime_numbers; //set where i push prime numbers
    std::set<long> not_prime_numbers; //set where i push the rest
    std::future<std::pair<long,bool>> allFutures[NUMBER_OF_THEADS]; 
    std::mutex _lock;

    
    TrialDivision tridv;
    MillerRabin mira;

    std::vector<PrimeCheckerIF*> algorithms = { &tridv, &mira };
    std::vector<long> data = generator1.read_from_file(DataSetSize);
    auto vec_size = data.size();
    auto current_number = data.begin(); // using iterator to keep track of current number to process

    for(auto alg:algorithms ){ //looping over every algorithm
        auto start = std::chrono::system_clock::now();
        //start first threads; without that the 'wait_for' future condition in while loop (couple lines below) never will be met 
        for(int i=0; i<NUMBER_OF_THEADS; i++){
            allFutures[i] = std::async(std::launch::async, PrimeCheckerIF::check_prime_thread, alg, *current_number);
            // arr.pop_back();
            current_number++;
            cnt++;
        }
        
        while ( prime_numbers.size() + not_prime_numbers.size()!=vec_size ){
            for(int i=0; i < NUMBER_OF_THEADS; i++){
                try{ // try because there will be some weird behavior if not all threads are working
                    if(allFutures[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready){
                        _lock.lock();
                        auto r = allFutures[i].get();
                        if(r.second)
                            prime_numbers.insert(r.first);
                        else
                            not_prime_numbers.insert(r.first);

                        if(current_number != data.end()){
                            allFutures[i] = std::async(std::launch::async, PrimeCheckerIF::check_prime_thread, alg , *current_number);
                            current_number++;
                            cnt++;
                        }
                        _lock.unlock();
                    }
                }catch(const std::future_error& e){
                    //¯\_(ツ)_/¯ 
                }
            }
        }
        auto end = std::chrono::system_clock::now();
        auto elapsed =std::chrono::duration_cast<std::chrono::microseconds>( end - start);
        std::cout << "Time for " << alg->name() << " algorithm is " << elapsed.count() << std::endl; 
        std::cout<< "number of all elements: " <<vec_size << std::endl;
        std::cout<< "number of cnt elements: " <<cnt << std::endl;
        std::cout << "number of prime numbers in set: " << prime_numbers.size() << std::endl;
        std::cout << "number of regural numbers in set: " << not_prime_numbers.size() << std::endl;
        std::cout << "---------------------------------------------" <<std::endl;
        cnt = 0;
        prime_numbers.clear();
        not_prime_numbers.clear();
        current_number = data.begin();
    }
}

