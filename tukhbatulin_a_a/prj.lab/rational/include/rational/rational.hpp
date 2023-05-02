#pragma once

#ifndef RATIONALHPP
#define RATIONALHPP
#include <iosfwd>
#include <cstdint>


class Rational{
public:
    Rational();
	Rational(const Rational&) = default;
	Rational(const int32_t num_);
	Rational(int32_t num_, int32_t denom_);
	~Rational() = default;
	Rational& operator=(const Rational&) = default;

	Rational& operator+=(const Rational&) noexcept;
	Rational& operator-=(const Rational&) noexcept;
	Rational& operator*=(const Rational&) noexcept;
	Rational& operator/=(const Rational&);

	Rational operator-() noexcept;
	Rational& operator++() noexcept;
	Rational& operator--() noexcept;
	Rational operator++(int) noexcept;
	Rational operator--(int) noexcept;

	bool operator==(const Rational& rhs) const noexcept { return (num_ * rhs.denom_ == rhs.num_ * denom_); }
	bool operator==(const int rhs) const noexcept { return operator==(Rational(rhs)); }
	bool operator!=(const Rational& rhs) const noexcept { return !operator==(rhs); }
	bool operator!=(const int rhs) const noexcept { return operator!=(Rational(rhs)); }
	bool operator>(const Rational& rhs) const noexcept { return (num_ * rhs.denom_ > denom_ * rhs.num_); }
	bool operator>(const int rhs) const noexcept { return operator>(Rational(rhs)); }
	bool operator<=(const Rational& rhs) const noexcept { return !operator>(rhs); }
	bool operator<=(const int rhs) const noexcept { return operator<=(Rational(rhs)); }
	bool operator<(const Rational& rhs) const noexcept { return (num_ * rhs.denom_ < denom_ * rhs.num_); }
	bool operator<(const int rhs) const noexcept { return operator<(Rational(rhs)); }
	bool operator>=(const Rational& rhs) const noexcept { return !operator<(rhs); }
	bool operator>=(const int rhs) const noexcept { return operator>=(Rational(rhs)); }

    std::ostream& writeTo(std::ostream& ostrm) const noexcept;
    std::istream& readFrom(std::istream& istrm);

private:
    void gcd() noexcept;
    Rational gcd(int32_t num_, int32_t denom_) noexcept;
    Rational gcd(Rational& rhs) noexcept;
	
private:
    int32_t num_;
	int32_t denom_;
	static const char slash {'/'};

};

Rational operator+(const Rational&, const Rational&) noexcept;
Rational operator-(const Rational&, const Rational&) noexcept;
Rational operator*(const Rational&, const Rational&) noexcept;
Rational operator/(const Rational&, const Rational&);


Rational operator+(const Rational&, const int32_t&) noexcept;
Rational operator-(const Rational&, const int32_t&) noexcept;
Rational operator*(const Rational&, const int32_t&) noexcept;
Rational operator/(const Rational&, const int32_t&);

Rational pow(Rational, const int32_t);

std::ostream& operator<<(std::ostream& ostrm, const Rational& temp);
std::istream& operator>>(std::istream& istrm, Rational& temp);

#endif