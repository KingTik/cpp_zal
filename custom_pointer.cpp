#include <iostream>
#include <algorithm>
#include <utility>


template <typename T>
class twSmartPointer{

    T* pointer;

    public:
    twSmartPointer(){
        pointer = new T();
        
    }

    twSmartPointer(const twSmartPointer<T>& o) = delete;
    twSmartPointer(twSmartPointer<T>&& o) {
        std::cout << "move constructor" << std::endl;
        
        this->pointer = o.get();
        if(o.get() != nullptr){
            *(this->pointer) = *o;
            o.soft_reset();
        }
    }




    // twSmartPointer<T>& operator=(twSmartPointer<T>& o) = delete;
    // twSmartPointer<T>& operator=(twSmartPointer<T> o) = delete;
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
        if(this->pointer != nullptr){
            this->reset();
        }
    }


    void reset(){
        delete [] pointer;
        pointer = nullptr;
    }

    void swap(twSmartPointer<T>& o){
        std::swap(this->pointer, o.get());
    }

    void soft_reset(){
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
    std::cout << *pointer <<std::endl;
    
    twSmartPointer<int> pointer2;
    pointer2 = std::move(pointer);
    std::cout << *pointer2 <<std::endl;


    twSmartPointer<int> pointer3 = std::move(pointer2);
    std::cout << *pointer3 <<std::endl;

    twSmartPointer<int> pointer4;
    
    
    *pointer4 = 100;
    std::cout << "Swapping" <<std::endl;
    std::cout << "pointer3: " << *pointer3 <<std::endl;
    std::cout << "pointer4: " << *pointer4 <<std::endl;
    std::cout << "BAM" <<std::endl;
    pointer4.swap(pointer3);
    std::cout << "pointer3: " << *pointer3 <<std::endl;
    std::cout << "pointer4: " << *pointer4 <<std::endl;
    

}