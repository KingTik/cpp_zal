#include <iostream>
#include <array>
#include <cstring>
#include <algorithm>

template <typename T, size_t N>
class RingBuffer{
    std::array<T, N> _array;
    int _cursor = 0;

public:

    T operator[](int x){
        return this->_array[x];
    }

    void push(T data){
        // this code below was before our last lesson so no std::rotate
        // if( this->_cursor < N){
        //     this->_array[this->_cursor] = data;
        //     this->_cursor++;
        // }else{
        //     std::memmove(this->_array.data(), (this->_array.data()+1), (N-1)*sizeof(T));
        //     this->_array[N-1] = data;
        // }

        
         
        if( this->_cursor < N){
            this->_array[this->_cursor] = data;
            this->_cursor++;
        }else{
            std::rotate(this->_array.begin(), this->_array.begin()+1, this->_array.end());
            this->_array[N-1] = data;
        }
        
    }

    auto begin(){
        return this->_array.begin();
    }

    auto end(){
        return this->_array.end();
    }

    auto rbegin(){
        return this->_array.rbegin();
    }

    auto rend(){
        return this->_array.rend();
    }

    void display(){
        for(auto elem: this->_array){
            std::cout << elem << ", ";
        }
    }


};








int main(){


    RingBuffer<int, 5> ring;

    for(int i =1; i< 15; i++){
        ring.push(i);
        ring.display();
        std::cout << std::endl;
    }



}
