#pragma once

#ifndef ARRAYD_HPP
#include <cstdint>
#include <iosfwd>

class ArrayD{
public:
    ArrayD() noexcept;
    explicit ArrayD(const ptrdiff_t size, const double num = 0);
    ~ArrayD();
    ArrayD(const ArrayD&);
    ArrayD& operator=(const ArrayD&);
    void reserve(ptrdiff_t size) noexcept;

    double& operator[](const ptrdiff_t i);
    const double& operator[](const ptrdiff_t i) const;
    ptrdiff_t ssize() const noexcept;
    void resize(const ptrdiff_t new_size);
    void insert(const ptrdiff_t ind, const double value);
    void remove(const ptrdiff_t i);
    void push_back(double numb) noexcept;
    void pop_back();
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

private:
    double* data_;
    ptrdiff_t capacity_;
    ptrdiff_t size_;
};
#endif