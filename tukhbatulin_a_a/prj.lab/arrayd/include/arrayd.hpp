#pragma once 
#ifndef ARRAYDHHP 
#define ARRAYDHHP

#include <iosfwd> 
#include <cstddef> 


class ArrayD {
public:
	ArrayD();
	explicit ArrayD(const ptrdiff_t len);
	ArrayD(const ptrdiff_t len, const double num);
	explicit ArrayD(const ArrayD& rhs);
	~ArrayD();

	ptrdiff_t ssize() const noexcept;
	void resize(const ptrdiff_t new_size);
	void insert(const double value, const ptrdiff_t i);
	void remove(const ptrdiff_t i);
	void push_back(const double value);
	void pop_back();

	std::istream& readFrom(std::istream& istrm);
	std::ostream& writeTo(std::ostream& ostrm) const;

	ArrayD& operator=(const ArrayD& rhs);
	double& operator[](const ptrdiff_t i);
	const double& operator[](const ptrdiff_t i) const;



private:
	ptrdiff_t size_{ 0 };
	ptrdiff_t capacity_{ 0 };
	double* memory_{ nullptr };

	static const char separator_{ ',' };
};

std::istream& operator>>(std::istream& istrm, ArrayD& rhs);
std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
#endif

