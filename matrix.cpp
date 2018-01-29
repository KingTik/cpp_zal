#include <iostream>
#include <array>

template <typename T, size_t X, size_t Y>
class Matrix{
    std::array<std::array<T, X>, Y> _matrix = {};

public:
    Matrix() = default;
    Matrix( std::array<std::array<T, X>, Y> matrx): _matrix(matrx){}
    void display(){
        for(auto row: this->_matrix){
            for(auto element: row){
                std::cout << element << ", ";
            }
            std::cout << std::endl;
        }
    }

    // Bracket operator
    std::array<T,X>& operator[](int x){
        return this->_matrix[x];
    }

    // Adding operator
    Matrix<T, X, Y> operator+(Matrix<T, X, Y> m2) {
         
        Matrix<T, X, Y> result;
        
        for(int i = 0; i < X ; i++){
            for(int j = 0; j< Y; j++ ){
                result[i][j] = this->_matrix[i][j] + m2[i][j];
            }
        }
        return result;
     }

    // Subtraction operator
    Matrix<T, X, Y> operator-(Matrix<T, X, Y> m2) {
         
        Matrix<T, X, Y> result;
        
        for(int i = 0; i < X ; i++){
            for(int j = 0; j< Y; j++ ){
                result[i][j] = this->_matrix[i][j] - m2[i][j];
            }
        }
        return result;
     }

    template <size_t p>
    auto operator*(const Matrix<T, Y ,p > m2){
        Matrix<T, X, p> result;

    for(int i = 0; i < X; ++i){
            for(int j = 0; j < p; ++j){
                for(int k = 0; k < Y; ++k)
                {
                    result[i][j] += this->_matrix[i][k] * m2[k][j];
                }
            }
    }
    return result;
    }


    auto operator*(const int scalar){
        Matrix<T, X, Y> result;
        
        for(int i = 0; i < X ; i++){
            for(int j = 0; j< Y; j++ ){
                result[i][j] = this->_matrix[i][j] * scalar;
            }
        }
        return result;
        
    }


    auto operator+(const int scalar){
        Matrix<T, X, Y> result;
        
        for(int i = 0; i < X ; i++){
            for(int j = 0; j< Y; j++ ){
                result[i][j] = this->_matrix[i][j] + scalar;
            }
        }
        return result;
    }



}; //END OF MATRIX

//global operator overload
template <typename T, size_t X, size_t Y>
auto operator*( int scalar,Matrix<T,X ,Y> &M){
    
    return M * scalar;
} 

//glonal overload for +
template <typename T, size_t X, size_t Y>
auto operator+( int scalar,Matrix<T,X ,Y> &M){

    return M + scalar;
} 


int main(){


    Matrix<int, 4,4> m1 = ( std::array<std::array<int, 4>, 4>) { {{-1,-2,-3,-4}, {-11,-12,-13,-14}, {-21,-22,-23,-24}, {-31,-32,-33,-34}} };
    Matrix<int, 4,4> m2 = ( std::array<std::array<int, 4>, 4>) { {{-1,-2,-3,-4}, {-11,-12,-13,-14}, {-21,-22,-23,-24}, {-31,-32,-33,-34}} };

    Matrix<int, 4,4> m3 = 3+ m1 ;

    // auto m4 = m1*m2;

    m3.display();

}