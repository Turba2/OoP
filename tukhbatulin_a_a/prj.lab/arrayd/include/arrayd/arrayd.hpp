#pragma once

#ifndef ARRAYD_HPP
#define ARRAYD_HPP

#include <iosfwd>
#include <cstdint>

template <typename T = double>

class ArrayD{
public:

    ArrayD() noexcept{
        ssize_ = 0;
        capacity_ = 1;
        data_ = reinterpret_cast<T*>(new int8_t[sizeof(T)]);
        //data_ = new T[capacity_];
    }

    ArrayD(ptrdiff_t size){
        if(size < 0){
            throw std::invalid_argument("bad size");
        }
        data_ = reinterpret_cast<T*>(new int8_t[2 * size * sizeof(T)]);
        ssize_ = size;
        capacity_ = size;
        ptrdiff_t i = 0;
        try{
            for(; i < ssize_; ++i){
                new (data_ + i) T(); // placement new
            }
        } catch(...){
            for(ptrdiff_t j = 0; j < i; ++j){
                (data_ + j)->~T();
            }
            delete[] reinterpret_cast<char*>(data_);
            throw;
        }
    }
    ArrayD(const ArrayD& other) noexcept{
        T* data_ = reinterpret_cast<T*>(new int8_t[other.ssize_ * sizeof(T)]);
        ssize_ = other.ssize_;
        capacity_ = other.capacity_;
        ptrdiff_t i = 0;
        try{
            for(; i < ssize_; ++i){
                new (data_ + i) T(other.data_[i]);
            }
        } catch(...){
            for(ptrdiff_t j = 0; j < i; ++j){
                (data_ + j)->~T();
            }
            delete[] reinterpret_cast<char*>(data_);
            throw;
        }
    }

    ArrayD& operator=(const ArrayD& rhs) noexcept{
        capacity_ = rhs.capacity_;
        ptrdiff_t i = 0;
        for(ptrdiff_t i = 0; i < ssize_; ++i){
            (data_ + i)->~T();
        }
        reserve(capacity_);
        for(i = 0; i < rhs.ssize_; ++i){
            new (data_ + i) T(rhs.data_[i]);
        }
        ssize_ = rhs.ssize_;
        return *this;
    }

    void reserve(ptrdiff_t size){
        if (size < 0){
            throw std::invalid_argument("bad size");
        }
        if(size <= capacity_) return;
        T* newarr = reinterpret_cast<T*>(new int8_t[size * sizeof(T)]);
        ptrdiff_t i = 0;
        try{
            for(; i < ssize_; ++i){
                new (newarr + i) T(data_[i]); // placement new
            }
        } catch(...){
            for(ptrdiff_t j = 0; j < i; ++j){
                (newarr + j)->~T();
            }
            delete[] reinterpret_cast<char*>(newarr);
            throw;
        }
        for(ptrdiff_t i = 0; i < ssize_; ++i){
            (data_ + i)->~T();
        }
        delete[] reinterpret_cast<char*>(data_);
        data_ = newarr;
        capacity_ = size;
    }

    void resize(const ptrdiff_t size, const T& value = T()){
        if (size < 0){
            throw std::invalid_argument("bad size");
        }
        if(size > capacity_) reserve(size);
        for(ptrdiff_t i = ssize_; i < size; ++i){
            new (data_ + i) T(value);
        }
        if(size < ssize_){
            ssize_ = size;
        }
    }

    void push_back(const T& value) noexcept{
        if(capacity_ == ssize_) reserve(2 * capacity_);
        new(data_ + ssize_) T(value);
        ssize_ += 1;
    } 

    void pop_back(){
        if(ssize_ <= 0){
            throw std::out_of_range("Dynamic ArrayD is empty");
        }
        ssize_ -= 1;
        (data_ + ssize_)->~T();
    }


    T& operator[](ptrdiff_t index){
        if(index < 0 || index >= ssize_){
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& operator[](ptrdiff_t index) const{
        if(index < 0 || index >= ssize_){
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    bool operator==(const ArrayD& rhs) noexcept{
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

    ptrdiff_t ssize() const noexcept{
        return ssize_;
    }

    void insert(const ptrdiff_t ind, const T& value){
        if(ind > ssize_ || ind < 0){
            throw std::out_of_range("Index out of range");
        }
        if(ssize_ == capacity_) reserve(2 * capacity_);
        T* newarr = reinterpret_cast<T*>(new int8_t[(ssize_ + 3) * sizeof(T)]);
        ptrdiff_t i = 0;
        try{
            for(; i < ind; ++i){
                new (newarr + i) T(data_[i]);
            }
            new (newarr + ind) T(value);
            for(i = ind; i < ssize_; ++i){
                new (newarr + i + 1) T(data_[i]);
            }
        }
        catch(...){
            for(i = 0; i < ssize_ + 3; ++i){
                (newarr + i)->~T();
            }
        }
        for(i = 0; i < ssize_; ++i){
            (data_ + i)->~T();
        }
        for(i = 0; i < ssize_ + 1; ++i){
            new (data_ + i) T(newarr[i]);
        }
        for(i = 0; i < ssize_ + 1; ++i){
            (newarr + i)->~T();
        }
        delete[] reinterpret_cast<char*>(newarr); 
        ssize_ += 1;
    }

    void remove(const ptrdiff_t ind){
        if (ind >= ssize_ || ind < 0){
            throw std::out_of_range("Index out of range");
        }
        T* newarr = reinterpret_cast<T*>(new int8_t[ssize_ * sizeof(T)]);
        ptrdiff_t i = 0;
        try{
            for(; i < ssize_; ++i){
                new (newarr + i) T(data_[i]);
            }
        }
        catch(...){
            for(i = 0; i < ssize_ - ind + 1; ++i){
                (newarr + i)->~T();
            }
            throw;
        }
        i = ind;
        (data_ + ind)->~T();
        for(; i < ssize_ - 1; ++i){
            (data_ + i)->~T();
            new(data_ + i) T(newarr[i + 1]);
        }
        for(i = 0; i < ssize_; ++i){
            (newarr + i)->~T();
        }
        delete[] reinterpret_cast<char*>(newarr); 
        ssize_ -= 1;
    }


private:
    T* data_;
    ptrdiff_t ssize_;
    ptrdiff_t capacity_;
};

#endif