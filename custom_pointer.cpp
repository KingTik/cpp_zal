#include <iostream>



template <typename T>
class twSmartPointer{

    T* pointer;

    public:
    twSmartPointer(){
        pointer = new T();
        
    }

    twSmartPointer(const twSmartPointer<T>& o) = delete;
    twSmartPointer(const twSmartPointer<T>&& o) {
        this->pointer = o.get();
        *(this->pointer) = *o;
        o.reset();
    }

    ~twSmartPointer(){
        
        this->reset();
    }

    void reset(){
        delete [] pointer;
        pointer = nullptr;
    }

    twSmartPointer<T>& operator=(twSmartPointer<T>&& o){
        this->reset();
        this->pointer = o.get();
        *(this->pointer) = *o;
        o.reset();

    }

    auto get() const{
        return pointer;
    }

    auto operator->()const{
        return get();
    }

    auto& operator*() const{
        return *pointer;
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

int main(){
    
    twSmartPointer<int> pointer;
    twSmartPointer<int> pointer2;
    std::cout << *pointer <<std::endl;
    *pointer = 11;
    std::cout << *pointer <<std::endl;


    if(pointer != pointer){
        std::cout << "Equal" <<std::endl;
    }else{
        std::cout << "Not Equal" <<std::endl;
    }
}