#include <matrixs/matrixs.hpp>
#include <algorithm>
#include <iostream>

MatrixS::MatrixS(MatrixS::SizeType size){
    if(get<0>(size) < 0 || get<1>(size) < 0){
        throw std::invalid_argument("bad size");
    }
    borders_ = size;
    data_point_ = new int* [get<0>(size)];
    data_ = new int[get<0>(size) * get<1>(size)];
    std::fill(data_, data_ + get<0>(size) * get<1>(size), 0);


    for(ptrdiff_t i = 0; i < get<0>(size); ++i){
       new (data_point_ + i) int*(data_ + i * get<1>(size));
    }
}

MatrixS::MatrixS(const ptrdiff_t m, const ptrdiff_t n){
    if(m < 0 || n < 0){
        throw std::invalid_argument("bad size");
    }
    data_point_ = new int* [m];
    data_ = new int[m * n];
    std::fill(data_, data_ + m * n, 0);
    for(ptrdiff_t i = 0; i < m; ++i){
       new (data_point_ + i) int*(data_ + i * n);
    }
    borders_ = SizeType(m, n);
}


MatrixS::~MatrixS(){
    delete[] reinterpret_cast<char*>(data_point_);
    delete[] reinterpret_cast<char*>(data_);
}

MatrixS::MatrixS(const MatrixS &other){
    borders_ = other.borders_;
    data_point_ = new int* [get<0>(borders_)];
    data_ = new int[get<0>(borders_) * get<1>(borders_)];

    std::uninitialized_copy(other.data_, other.data_+ get<0>(other.borders_) * get<1>(other.borders_), data_);
    
    for(ptrdiff_t i = 0; i < get<0>(borders_); ++i){
       new (data_point_ + i) int*(data_ + i * get<1>(borders_));
    }

}

MatrixS &MatrixS::operator=(const MatrixS &other){
    if(other.borders_ != borders_){
        delete[] reinterpret_cast<char*>(data_point_);
        delete[] reinterpret_cast<char*>(data_);
    }
    borders_ = other.borders_;
    data_point_ = new int* [get<0>(borders_)];
    data_ = new int[get<0>(borders_) * get<1>(borders_)];

    std::uninitialized_copy(other.data_, other.data_+ get<0>(borders_) * get<1>(borders_), data_);
    for(ptrdiff_t i = 0; i < get<0>(borders_); ++i){
       new (data_point_ + i) int*(data_ + i * get<1>(borders_));
    }

    return *this;
}

int& MatrixS::at(const SizeType elem){
    if((0 <= get<0>(elem) && get<0>(elem) < get<0>(borders_)) && (0 <= get<1>(elem) && get<1>(elem) < get<1>(borders_))){
        return *(data_point_[get<0>(elem)] + get<1>(elem));
    }
    throw std::out_of_range("Wrong position");
}

const int& MatrixS::at(const SizeType elem) const{
    if((0 <= get<0>(elem) && get<0>(elem) < get<0>(borders_)) && (0 <= get<1>(elem) && get<1>(elem) < get<1>(borders_))){
        return *(data_point_[get<0>(elem)] + get<1>(elem));
    }
    throw std::out_of_range("Wrong position");
}

int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j){
    if((0 <= i && i < get<0>(borders_)) && (0 <= j && j < get<1>(borders_))){
        return *(data_point_[i] + j);
    }
    throw std::out_of_range("Wrong position");
}

const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const{
    if((0 <= i && i < get<0>(borders_)) && (0 <= j && j < get<1>(borders_))){
        return *(data_point_[i] + j);
    }
    throw std::out_of_range("Wrong position");
}

MatrixS::SizeType MatrixS::ssize() const noexcept{
    return borders_; 
}

void MatrixS::resize(const SizeType new_size){
    try{
        *this = MatrixS(new_size);
    }
    catch(...){
        throw;
    }
}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j){
    try{
        *this = MatrixS(SizeType(i, j));
    }
    catch(...){
        throw;
    }
}

ptrdiff_t MatrixS::nRows() const noexcept{
    return get<0>(borders_);

}

ptrdiff_t MatrixS::nCols() const noexcept{
    return get<1>(borders_);
}
