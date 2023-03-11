#include <rational/rational.hpp>
#include <iostream>

void Rational::gcd() {
	int32_t a, b;
	a = abs(num); b = denum;
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	num /= a;
	denum /= a;
}

Rational Rational::gcd(int32_t num, int32_t denum) {
	int32_t a, b;
	a = abs(num); b = denum;
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	return Rational(num / a, denum / a);
}

Rational Rational::gcd(Rational& rhs) {
	int32_t a, b;
	a = abs(rhs.num); b = rhs.denum;
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	return Rational(rhs.num / a, rhs.denum / a);
}



Rational::Rational() : num(0), denum(1) {}
Rational::Rational(const Rational& tmpCop) : num(tmpCop.num), denum(tmpCop.denum) {}
Rational::Rational(const int32_t& num) : num(num), denum(1) {}

Rational::Rational(int32_t temp_num, int32_t temp_denum) {
	if (temp_denum < 0) {
		temp_denum *= -1;
		temp_num *= -1;
	}
	if (temp_denum == 0) {
		throw std::invalid_argument("Divide by zero exception");
	}
	num = temp_num;
	denum = temp_denum;
	gcd();
}
//~Rational() = default;


Rational& Rational::operator+=(const Rational& temp) {
	num = num * temp.denum + denum * temp.num;
	denum = denum * temp.denum;
	gcd();
	return *this;
}

Rational& Rational::operator-=(const Rational& temp) {
	num = num * temp.denum - denum * temp.num;
	denum = denum * temp.denum;
	gcd();
	return *this;
}

Rational& Rational::operator*=(const Rational& temp) {
	num *= temp.num;
	denum *= temp.denum;
	gcd();
	return *this;
}

Rational& Rational::operator/=(const Rational& temp) {
	if (temp.num == 0) {
		throw std::invalid_argument("invalid argument");
		//return 0; // ERROR!
	}
	num *= temp.denum;
	denum *= temp.num;
	gcd();
	return *this;
}

Rational& Rational::operator++() {
	*this = *this + 1;
	return *this;
}

Rational& Rational::operator--() {
	*this = *this - 1;
	return *this;
}


Rational& Rational::operator++(int32_t) {
	Rational plus(*this);
	++(*this);
	return plus;
}

Rational& Rational::operator--(int32_t) {
	Rational minus(*this);
	--(*this);
	return minus;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational sum = lhs;
	sum += rhs;
	return sum;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	Rational minus = lhs;
	minus -= rhs;
	return minus;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational multipl = lhs;
	multipl *= rhs;
	return multipl;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	Rational division = lhs;
	division /= rhs;
	return division;
}

Rational operator+(const Rational& lhs, const int32_t& temp) {
	Rational sum = lhs;
	sum += Rational(temp);
	return sum;
}

Rational operator-(const Rational& lhs, const int32_t& temp) {
	Rational minus = lhs;
	minus -= Rational(temp);
	return minus;
}

Rational operator*(const Rational& lhs, const int32_t& temp) {
	Rational multipl = lhs;
	multipl *= Rational(temp);
	return multipl;
}

Rational operator/(const Rational& lhs, const int32_t& temp) {
	if (temp == 0) {
		throw std::invalid_argument("invalid argument");
		//return 0; // ERROR!
	}
	Rational divis = lhs;
	divis /= Rational(temp);
	return divis;
}

bool Rational::operator==(const Rational& rhs) const {
	return (num == rhs.num && denum == rhs.denum);
}

bool Rational::operator>(const Rational& rhs) const {
	return (num * rhs.denum > denum * rhs.num);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs) && !(lhs > rhs);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
	return (lhs == rhs) || (lhs > rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
	return (lhs == rhs) || (lhs < rhs);
}

Rational pow(Rational temp, int32_t k) {
	if (k == 0) {
		return Rational(1);
	}
	if (k < 0) {
		if (temp == 0) {
			throw std::invalid_argument("invalid argument");
			return temp;
			//return temp; // ERROR!
		}
		temp = (1 / temp);
		k *= -1;
	}
	Rational vr(1);
	while (k) {
		if (k & 1) {
			vr *= temp;
		}
		temp *= temp;
		k >>= 1;
	}
	return vr;
}


std::ostream& operator<<(std::ostream& ostrm, const Rational& temp) {
	return temp.writeTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& temp) {
	return temp.readFrom(istrm);
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const {
	ostrm << num << slash << denum;
	return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm) {
	int32_t tmp_num(0), tmp_denum(0);
	char symb(0);
	istrm >> tmp_num >> symb >> tmp_denum;
	if (istrm.good()) {
		if (symb == slash) {
			num = tmp_num;
			denum = tmp_denum;
			gcd();
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}
