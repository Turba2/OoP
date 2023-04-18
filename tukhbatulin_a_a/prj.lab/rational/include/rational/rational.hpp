#pragma once

#ifndef RATIONALHPP
#define RATIONALHPP
#include <iosfwd>
#include <cstdint>


class Rational {
public:
	Rational();
	Rational(const Rational&);
	Rational(const int32_t& num);
	Rational(int32_t num, int32_t denum);

	Rational& operator+=(const Rational&);
	Rational& operator-=(const Rational&);
	Rational& operator*=(const Rational&);
	Rational& operator/=(const Rational&);

	Rational& operator++();
	Rational& operator--();
	Rational& operator++(const int32_t);
	Rational& operator--(const int32_t); 

	bool operator==(const Rational&) const;
	bool operator>(const Rational&) const;

	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);

private:
	void gcd();
	Rational gcd(int32_t num, int32_t denum);
	Rational gcd(Rational& rhs);

private:
	int32_t num;
	int32_t denum;
	static const char slash = '/';

};

Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);


Rational operator+(const Rational&, const int32_t&);
Rational operator-(const Rational&, const int32_t&);
Rational operator*(const Rational&, const int32_t&);
Rational operator/(const Rational&, const int32_t&);

bool operator<(const Rational&, const Rational&);
bool operator!=(const Rational&, const Rational&);
bool operator<=(const Rational&, const Rational&);
bool operator>=(const Rational&, const Rational&);

Rational pow(Rational, const int32_t);

std::ostream& operator<<(std::ostream& ostrm, const Rational& temp);
std::istream& operator>>(std::istream& istrm, Rational& temp);

#endif

















