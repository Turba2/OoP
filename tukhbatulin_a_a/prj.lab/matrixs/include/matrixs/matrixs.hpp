#pragma once

#ifndef MATRIXS_HPP
#define MATRIXS_HPP
#include <iosfwd>
#include <cstdint>
#include <utility>
#include <memory>

class MatrixS {    
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

    MatrixS(const SizeType size = {0, 0});
    MatrixS(const ptrdiff_t m, const ptrdiff_t n);

    ~MatrixS();

    MatrixS(const MatrixS& other);
    MatrixS& operator=(const MatrixS& other);

    int& at(const SizeType elem);
    const int& at(const SizeType elem) const;
    int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
    const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

    SizeType ssize() const noexcept;

    void resize(const SizeType new_size);
    void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);
    
    std::ptrdiff_t nRows() const noexcept;
    std::ptrdiff_t nCols() const noexcept;

private:
    SizeType borders_;
    int* data_;
    int** data_point_;
};


#endif