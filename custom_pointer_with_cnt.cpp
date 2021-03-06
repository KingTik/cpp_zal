#include <iostream>
#include <algorithm>
#include <utility>

struct Counter{
    int _cnt = 0;
    public:
    int get(){
        return _cnt;
    }

    void dec(){
        _cnt--;
    }

    void reset(){
        _cnt = 0;
    }
    void inc(){
        _cnt++;
    }
};



template <typename T>
class twSmartPointer{

    public:
    T* pointer;
    Counter* _counter;

    twSmartPointer(){
        pointer = new T();
        _counter = new Counter;
        
    }

    twSmartPointer(twSmartPointer<T>& o){
        std::cout << "copy constructor" <<std::endl;
        this->pointer = o.pointer;
        this->_counter = o._counter;
        _counter->inc();

    };
    twSmartPointer(twSmartPointer<T>&& o) {
        std::cout << "move constructor" << std::endl;
        
        this->pointer = o.get();
        if(o.get() != nullptr){
            *(this->pointer) = *o;
            this->_counter = o._counter;
            o.soft_reset();
        }
    }




    twSmartPointer<T>& operator=(twSmartPointer<T>& o) {
        std::cout << "assign operator";
        this->reset();
        this->_counter = o._counter;
        this->pointer = o.pointer;
        this->_counter->inc();
        //to do
    }
    
    twSmartPointer<T>& operator=(twSmartPointer<T>&& o){
        std::cout << "move assign" << std::endl;
        this->reset();
        this->pointer = o.get();
        if(o.get() != nullptr){
            *(this->pointer) = *o;
            o.soft_reset();
        }
    }

    ~twSmartPointer(){
        std::cout << "Destruktor" <<std::endl;
        if(_counter->get() == 0){
            if(this->pointer != nullptr){
                this->reset();
            }
        }else{
            std::cout <<" subtracting counter" <<std::endl;
            _counter->dec();
        }
    }


    void reset(){
        
        if(pointer != nullptr){
            std::cout << "deleting" <<std::endl;
            delete [] pointer;
            _counter->reset();
            pointer = nullptr;
        }
    }

    void swap(twSmartPointer<T>& o){
        std::swap(this->pointer, o.get());
        std::swap(this->_counter, o._counter);
    }

    void soft_reset(){
        _counter->reset();
        this->pointer = nullptr;
    }

    auto& get(){
        return pointer;
    }

    auto operator->()const{
        return get();
    }

    auto& operator*() const{
        if(this->pointer != nullptr){
            return *pointer;
        }else{
            throw;
        }
    }
};

template <typename T>
bool operator==(const twSmartPointer<T>& left, const twSmartPointer<T>& right){
    return left.get() == right.get();
}

template <typename T>
bool operator!=(const twSmartPointer<T>& left, const twSmartPointer<T>& right){
    return left.get() != right.get();
}

template <typename T>
bool operator>(const twSmartPointer<T>& left, const twSmartPointer<T>& right){
    return left.get() > right.get();
}

template <typename T>
bool operator>=(const twSmartPointer<T>& left, const twSmartPointer<T>& right){
    return left.get() >= right.get();
}

template <typename T>
bool operator<(const twSmartPointer<T>& left, const twSmartPointer<T>& right){
    return left.get() < right.get();
}

template <typename T>
bool operator<=(const twSmartPointer<T>& left, const twSmartPointer<T>& right){
    return left.get() <= right.get();
}


auto foo(){
    twSmartPointer<int> ppp;
    *ppp = 14;
    return ppp;
}


int main(){
    
    twSmartPointer<int> pointer;
    std::cout << *pointer <<std::endl;
    *pointer = 11;

    twSmartPointer<int> pointer2(pointer);
    {
        twSmartPointer<int> pointer3(pointer);
        std::cout << pointer._counter->get() <<std::endl;
    }
    std::cout << pointer._counter->get() <<std::endl;


    twSmartPointer<int> pointer4;
    pointer4 = pointer2;
    std::cout << pointer._counter->get() <<std::endl;
    // std::cout << *(pointer2._counter) <<std::endl;

}