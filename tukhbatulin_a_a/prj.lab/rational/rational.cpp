#include <rational/rational.hpp>
#include <iostream>

void Rational::gcd() noexcept{
	int32_t a, b;
	a = abs(num_); b = denom_;
	while(b){
		a %= b;
		std::swap(a, b);
	}
	num_ /= a;
	denom_ /= a;
}

Rational Rational::gcd(int32_t num_, int32_t denom_) noexcept{
	int32_t a, b;
	a = abs(num_); b = denom_;
	while(b){
		a %= b;
		std::swap(a, b);
	}
	return Rational(num_ / a, denom_ / a);
}

Rational Rational::gcd(Rational& rhs) noexcept{
	int32_t a, b;
	a = abs(rhs.num_); b = rhs.denom_;
	while(b){
		a %= b;
		std::swap(a, b);
	}
	return Rational(rhs.num_ / a, rhs.denom_ / a);
}


Rational::Rational() : num_(0), denom_(1) {}
Rational::Rational(const int32_t num_): num_(num_), denom_(1){}

Rational::Rational(int32_t temp_num_, int32_t temp_denom_){
	if(temp_denom_ < 0){
		temp_denom_ *= -1;
		temp_num_ *= -1;
	}
	if(temp_denom_ == 0){
		throw std::invalid_argument("Divide by zero exception");
	}
	num_ = temp_num_;
	denom_ = temp_denom_;
	gcd();
}
//~Rational() = default;


Rational& Rational::operator+=(const Rational& temp) noexcept{
	num_ =  num_ * temp.denom_ + denom_ * temp.num_;
	denom_ = denom_ * temp.denom_;
	gcd();
	return *this;
}

Rational& Rational::operator-=(const Rational& temp) noexcept{
	num_ =  num_ * temp.denom_ - denom_ * temp.num_;
	denom_ = denom_ * temp.denom_;
	gcd();
	return *this;
}

Rational& Rational::operator*=(const Rational& temp) noexcept{
	num_ *= temp.num_;
	denom_ *= temp.denom_;
	gcd();
	return *this;
}

Rational& Rational::operator/=(const Rational& temp){
	if(temp.num_ == 0){
		throw std::invalid_argument("invalid argument");
		//return 0; // ERROR!
	}
	num_ *= temp.denom_;
	denom_ *= temp.num_;
	gcd();
	return *this;
}

Rational Rational::operator-() noexcept {
	return Rational(-num_, denom_);
}

Rational& Rational::operator++() noexcept{
	*this = *this + 1;
	return *this;
}

Rational& Rational::operator--() noexcept{
	*this = *this - 1;
	return *this;
}

Rational Rational::operator++(int) noexcept{
	Rational res(num_, denom_);
	++*this;
	return res;
}

Rational Rational::operator--(int) noexcept{
	Rational res(num_, denom_);
	--*this;
	return res;
}

Rational operator+(const Rational& lhs, const Rational& rhs) noexcept{
	Rational sum = lhs;
	sum += rhs;
	return sum;
}

Rational operator-(const Rational& lhs, const Rational& rhs) noexcept{
	Rational minus = lhs;
	minus -= rhs;
	return minus;
}

Rational operator*(const Rational& lhs, const Rational& rhs) noexcept{
	Rational multipl = lhs;
	multipl *= rhs;
	return multipl;
}

Rational operator/(const Rational& lhs, const Rational& rhs){
	Rational division = lhs;
	division /= rhs;
	return division;
}

Rational operator+(const Rational& lhs, const int32_t& temp) noexcept{
	Rational sum = lhs;
	sum += Rational(temp);
	return sum;
}

Rational operator-(const Rational& lhs, const int32_t& temp) noexcept{
	Rational minus = lhs;
	minus -= Rational(temp);
	return minus;
}

Rational operator*(const Rational& lhs, const int32_t& temp) noexcept{
	Rational multipl = lhs;
	multipl *= Rational(temp);
	return multipl;
}

Rational operator/(const Rational& lhs, const int32_t& temp){
	if(temp == 0){
		throw std::invalid_argument("invalid argument");
		//return 0; // ERROR!
	}
	Rational divis = lhs;
	divis /= Rational(temp);
	return divis;
}

Rational pow(Rational temp, int32_t k) {
	if (k == 0){
		return Rational(1);
	}
	if(k < 0){
		if (temp == 0){
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


std::ostream& operator<<(std::ostream& ostrm, const Rational& temp){
	return temp.writeTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& temp){
	return temp.readFrom(istrm);
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const noexcept{
	ostrm << num_ << slash << denom_;
	return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm){
	int32_t tmp_num_(0), tmp_denom_(0);
	char symb(0);
	istrm >> tmp_num_;
	if(isspace(istrm.peek())){
		istrm.setstate(std::ios_base::failbit);
		istrm.setstate(std::ios_base::eofbit);
	}
	istrm >> symb; 
	if (isspace(istrm.peek()) || symb != slash){
		istrm.setstate(std::ios_base::failbit);
		istrm.setstate(std::ios_base::eofbit);
	}
	istrm >> tmp_denom_;
	if (tmp_denom_ <= 0){
		istrm.setstate(std::ios_base::failbit);
		istrm.setstate(std::ios_base::eofbit);
	}
	if(istrm.good()){
		num_ = tmp_num_;
		denom_ = tmp_denom_;
		gcd();
	}
	return istrm;
}
