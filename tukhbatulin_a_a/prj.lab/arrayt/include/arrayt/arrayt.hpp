#pragma once

#ifndef ARRAYT_HPP

#include <cstdint>
#include <iosfwd>

template <typename T>
class ArrayT{
public:
    ArrayT() noexcept;
    explicit ArrayT(const ptrdiff_t size, const T num = T());
    ~ArrayT();
    ArrayT(const ArrayT&);
    ArrayT& operator=(const ArrayT&);
    void reserve(ptrdiff_t size) noexcept;

    T& operator[](const ptrdiff_t i);
    const T& operator[](const ptrdiff_t i) const;
    ptrdiff_t ssize() const noexcept;
    void resize(const ptrdiff_t new_size);
    void insert(const ptrdiff_t ind, const T value = T());
    void remove(const ptrdiff_t i);
    void push_back(double numb) noexcept;
    void pop_back();
    bool operator==(const ArrayT& rhs) noexcept{
        if(this->ssize() != rhs.ssize()){
            return 0;
        }
        bool fl = 1;

        for(ptrdiff_t i = 0; i < rhs.ssize(); ++i){
            if(this->data_[i] != rhs.data_[i]){
                fl = 0;
            }
        }
        return fl;
    }

private:
    T* data_;
    ptrdiff_t capacity_;
    ptrdiff_t size_;
};



template <typename T> ArrayT<T>::ArrayT() noexcept{
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

template<class T> ArrayT<T>::ArrayT(ptrdiff_t size, T num){
    if (size < 0) {
        throw std::invalid_argument("Invalid argument");
    }
    capacity_ = size;
    if(size == 0){
        capacity_ = 0;
    }
    size_ = size;
    data_ = new T[size];
    std::fill(data_, data_ + size, num);
}

template<class T> ArrayT<T>::ArrayT(const ArrayT<T> &temp){
    data_ = new T[temp.capacity_];
    std::uninitialized_copy(temp.data_, temp.data_ + temp.size_, data_);
    size_ = temp.size_;
    capacity_ = temp.capacity_;
}


template<class T> ArrayT<T>::~ArrayT(){
    delete[] data_;
}

template<class T> ArrayT<T> &ArrayT<T>::operator=(const ArrayT<T> &rhs){
    if (this == &rhs) {
        return *this;
    }
    delete[] reinterpret_cast<char*>(data_);
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_ = new T[size_];
    std::uninitialized_copy(rhs.data_, rhs.data_ + size_, data_);
    return *this;
}

template<class T> ptrdiff_t ArrayT<T>::ssize() const noexcept{
    return size_;
}


template<class T> T &ArrayT<T>::operator[](ptrdiff_t index){
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<class T> const T &ArrayT<T>::operator[](ptrdiff_t index) const{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<class T> void ArrayT<T>::reserve(ptrdiff_t size) noexcept{
    if(size < capacity_){
        return;
    }
    double* newarr = new double[capacity_];
    std::uninitialized_copy(data_, data_ + capacity_, newarr);
    delete[] reinterpret_cast<char*>(data_);
    data_ = new T[size];
    std::uninitialized_copy(newarr, newarr + capacity_, data_);
    std::fill(data_ + size_, data_ + size, 0);
    capacity_ = size;
    delete[] reinterpret_cast<char*>(newarr);   
}

template<class T> void ArrayT<T>::resize(ptrdiff_t new_size){
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



template<class T> void ArrayT<T>::push_back(double numb) noexcept{
    if(size_ == capacity_){
        reserve(2 * capacity_);
    }
    data_[size_] = numb;
    size_ += 1;
}

template<class T> void ArrayT<T>::pop_back(){
    if(size_ == 0){
        throw std::out_of_range("List is empty");
    }
    size_ -= 1;

}

template<class T> void ArrayT<T>::insert(ptrdiff_t ind, T value){
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

template<class T> void ArrayT<T>::remove(ptrdiff_t ind){
    if (ind < 0 || ind >= size_) throw std::out_of_range("out of range");
    ptrdiff_t i = ind + 1;
    for(; i < size_; ++i){
        data_[i - 1] = data_[i];
    }
    size_ -= 1;
}

#endif // ARRAYT_HPP