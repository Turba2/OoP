#include <arrayd/arrayd.hpp>
#include <iostream>
#include <memory>

ArrayD::ArrayD() noexcept{
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

ArrayD::ArrayD(ptrdiff_t size, double num){
    if (size < 0) {
        throw std::invalid_argument("Invalid argument");
    }
    capacity_ = size;
    if(size == 0){
        capacity_ = 0;
    }
    size_ = size;
    data_ = new double[size];
    std::fill(data_, data_ + size, num);
}

ArrayD::ArrayD(const ArrayD &temp){
    data_ = new double[temp.capacity_];
    std::uninitialized_copy(temp.data_, temp.data_ + temp.size_, data_);
    size_ = temp.size_;
    capacity_ = temp.capacity_;
}
ArrayD::~ArrayD(){
    delete[] data_;
}

ArrayD &ArrayD::operator=(const ArrayD &rhs){
    if (this == &rhs) {
        return *this;
    }
    delete[] reinterpret_cast<char*>(data_);
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_ = new double[size_];
    std::uninitialized_copy(rhs.data_, rhs.data_ + size_, data_);
    return *this;
}
ptrdiff_t ArrayD::ssize() const noexcept{
    return size_;
}


double& ArrayD::operator[](const std::ptrdiff_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

const double& ArrayD::operator[](const std::ptrdiff_t index) const{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

void ArrayD::reserve(ptrdiff_t size) noexcept{
    if(size < capacity_){
        return;
    }
    double* newarr = new double[capacity_];
    std::uninitialized_copy(data_, data_ + capacity_, newarr);
    delete[] reinterpret_cast<char*>(data_);
    data_ = new double[size];
    std::uninitialized_copy(newarr, newarr + capacity_, data_);
    std::fill(data_ + size_, data_ + size, 0);
    capacity_ = size;
    delete[] reinterpret_cast<char*>(newarr);   
}

void ArrayD::resize(ptrdiff_t new_size){
    if (new_size <= 0){
        throw std::invalid_argument("Invalid argument");
    }
    if(new_size > capacity_){
        reserve(new_size);
    }
    if (new_size > size_){
        std::fill(data_ + size_, data_ + new_size, 0);
    }
    size_ = new_size;
    std::fill(data_ + size_, data_ + capacity_, 0);
}


void ArrayD::push_back(double numb) noexcept{
    if(size_ == capacity_){
        reserve(2 * capacity_);
    }
    data_[size_] = numb;
    size_ += 1;
}

void ArrayD::pop_back(){
    if(size_ == 0){
        throw std::out_of_range("List is empty");
    }
    size_ -= 1;

}

void ArrayD::insert(ptrdiff_t ind, double value){
    if(ind > size_ || ind < 0){
            throw std::out_of_range("Index out of range");
    }
    if (capacity_ == 0){reserve(2);}
    else if(size_ == capacity_) reserve(2 * capacity_);

    double* newarr = reinterpret_cast<double*>(new int8_t[(size_ + 3) * sizeof(double)]);
    ptrdiff_t i = 0;
    for(; i < ind; ++i){
        newarr[i] = data_[i];
    }
    newarr[ind] = value;
    for(i = ind; i < size_; ++i){
        newarr[i + 1] = data_[i];
    }
    size_ += 1;
    std::uninitialized_copy(newarr, newarr + size_, data_);
    delete[] reinterpret_cast<char*>(newarr);
}

void ArrayD::remove(ptrdiff_t ind){
    if (ind < 0 || ind >= size_) throw std::out_of_range("out of range");
    ptrdiff_t i = ind + 1;
    for(; i < size_; ++i){
        data_[i - 1] = data_[i];
    }
    size_ -= 1;
}