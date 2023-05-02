//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include <doctest/doctest.h>
#include <matrixs/matrixs.hpp>
#include <iostream>

MatrixS ar;

int main(){
    MatrixS::SizeType size = MatrixS::SizeType(40, 40);
    ar.resize(size);
    for(ptrdiff_t i = 0; i < ar.nRows(); ++i){
        for(ptrdiff_t j = 0; j < ar.nCols(); ++j){
            std::cout << ar.at(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------\n";
    for(ptrdiff_t i = 0; i < ar.nRows(); ++i){
        ar.at(i, i) = i + 1;
    }

    for(ptrdiff_t i = 0; i < ar.nRows(); ++i){
        for(ptrdiff_t j = 0; j < ar.nCols(); ++j){
            std::cout << ar.at(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
