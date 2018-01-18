#include <iostream>



template <typename T>
class twSmartPointer{

    T* pointer;

    public:
    twSmartPointer(){
        pointer = new T();
        *pointer = 10;
    }

    ~twSmartPointer(){
        
        delete [] pointer;
    }

    auto get() const{
        return pointer;
    }

    auto operator->()const{
        return get();
    }

    auto& operator*(){
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