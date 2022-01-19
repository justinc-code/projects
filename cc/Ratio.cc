#include "Ratio.h"

using namespace std;


// greatest common divisor and least common multiple found in geeks for geeks
// https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/
long gcd(int a, int b){
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

// Function to return LCM of two numbers
long lcm(int a, int b){
    return (a*b)/gcd(a, b);
}

int Ratio::count = 0;

void Ratio::normalize(long numerator, long denominator){
    long common = 1;

    if(denominator < 0){
        numerator *= -1;
        denominator *= -1;
    }

    if(numerator < 0){
        numerator *= -1;
        common = gcd(numerator, denominator);
        numerator_simp = -1*(numerator/ common);
        denominator_simp = denominator / common;
    }

   else{
		if(numerator != denominator){
				common = gcd(numerator, denominator);
				numerator_simp = numerator / common;
				denominator_simp = denominator /  common;
		}
		else{
				numerator_simp = 1;
				denominator_simp = 1;
		}
    }
}


Ratio::Ratio(long top, long bottom){

    if(bottom == 0){
        throw runtime_error("ERROR: Denominator Cannot Be 0");
    }
    normalize(top, bottom);
    count++;
}


Ratio::Ratio(int top, int bottom){

    if(bottom == 0){
        throw runtime_error("ERROR: Denominator Cannot Be 0");
        }
    normalize(top,bottom);
    count++;
}

// copy constructor
Ratio::Ratio(const Ratio &copy){
    numerator_simp = copy.numerator_simp;
    denominator_simp = copy.denominator_simp;
    count++;
}


// decrement object count since one less ratio object
Ratio::~Ratio(){
    count--;
}

//assignment operator
Ratio &Ratio::operator=(const Ratio &frac){

    numerator_simp = frac.numerator_simp;
    denominator_simp = frac.denominator_simp;

    return *this;
}


//returns the numerator as a long
long Ratio::numerator () const{

    return numerator_simp;
}

//sets the numerator as a long
void Ratio::numerator(long top){

    normalize(top, denominator_simp);
}


// returns the denominator as a long
long Ratio::denominator () const{

    return denominator_simp;
}


//sets the denominator as a long
void Ratio::denominator(long bottom){

    if(bottom == 0){
        throw runtime_error("ERROR: Denominator Cannot Be 0");
    }

    normalize(numerator_simp, bottom);
}


// returns ratio between the numerator and denominator
long double Ratio::ratio() const{

    return (1.0*numerator_simp) / denominator_simp;
}


// ratio + ratio
Ratio Ratio::operator+(const Ratio &right){

	Ratio storeSum (numerator(),denominator());
	storeSum += right;
	return storeSum;
}


// ratio + number
Ratio Ratio::operator+(const long add){

	Ratio storeSum(numerator(),denominator());
	storeSum += add;
	return storeSum;
}


// number + ratio
Ratio operator+(const long l,const Ratio &right){

	Ratio storeSum(l);
	storeSum += right;
	return storeSum;
}


// ratio - ratio
Ratio Ratio::operator-(const Ratio &right){

	Ratio storeDif(numerator(),denominator());
	storeDif -= right;
	return storeDif;
}


// ratio - number
Ratio Ratio::operator-(const long sub){

	Ratio storeDif(numerator(),denominator());
	storeDif -= sub;
	return storeDif;
}


// number - ratio
Ratio operator-(const long l, const Ratio &right){

	Ratio storeDif(l);
	storeDif -= right;
	return storeDif;
}


// ratio * ratio
Ratio Ratio::operator*(const Ratio &right){

	Ratio storeProd(numerator(),denominator());
	storeProd *= right;
	return storeProd;
}


// ratio * number
Ratio Ratio::operator*(const long prod){

	Ratio storeProd(numerator(),denominator());
	storeProd *= prod;
	return storeProd;
}


// number * ratio
Ratio operator*(const long l, const Ratio &right){

	Ratio storeProd(l);
	storeProd *= right;
	return storeProd;
}


// ratio / ratio
Ratio Ratio::operator/(const Ratio &right){

	Ratio storeDiv(numerator(),denominator());
	storeDiv /= right;
	return storeDiv;
}


// ratio / number
Ratio Ratio::operator/(const long div){

	Ratio storeDiv(numerator(),denominator());
	storeDiv /= div;
	return storeDiv;
}


// number / ratio
Ratio operator/(const long l, const Ratio &right){

	Ratio storeDiv(l);
	storeDiv /= right;
	return storeDiv;
}


// ratio += ratio
const Ratio &Ratio::operator+=(const Ratio &right){

	numerator_simp = numerator() * right.denominator() + right.numerator() * denominator();
	denominator_simp = denominator() * right.denominator();

	normalize(numerator_simp,denominator_simp);

	return *this;
}


// ratio += number
const Ratio &Ratio::operator+=(const long add){

	numerator_simp = numerator() + add * denominator();
	denominator_simp = denominator();

	normalize(numerator_simp,denominator_simp);

	return *this;
}


// ratio -= ratio
const Ratio &Ratio::operator-=(const Ratio &right){

	long leastMul = lcm(denominator(), right.denominator());
	long commonMultiple1 = denominator() / leastMul;
	long commonMultiple2 = right.denominator() / leastMul;

	numerator_simp = (numerator() * commonMultiple1) - (right.numerator() * commonMultiple2);
	denominator_simp = leastMul;

	normalize(numerator_simp,denominator_simp);

	return *this;
}


// ratio -= number
const Ratio &Ratio::operator-=(const long sub){
	
	numerator_simp =numerator() - sub * denominator();
	denominator_simp = denominator();

	normalize(numerator_simp, denominator_simp);
	return *this;
}


// ratio *= ratio
const Ratio &Ratio::operator*=(const Ratio &right){

	numerator_simp = numerator() * right.numerator();
	denominator_simp = denominator() * right.denominator();
	normalize(numerator_simp,denominator_simp);

	return *this;
}


// ratio *= number;
const Ratio &Ratio::operator*=(const long prod){

	numerator_simp = numerator() * prod;
	denominator_simp = denominator();
	normalize(numerator_simp,denominator_simp);

	return *this;
}


// ratio /= ratio
const Ratio &Ratio::operator/=(const Ratio &right){

	if(right.denominator() == 0){
			throw runtime_error("ERROR: Cannot Divide by 0");
	}
	numerator_simp = numerator() * right.denominator();
	denominator_simp = denominator() * right.numerator();

	normalize(numerator_simp,denominator_simp);

	return *this;
}


// ratio /= number
const Ratio &Ratio::operator/=(const long div){

	if(div == 0){
			throw runtime_error("ERROR: Cannot Divide by 0");
			}

	numerator_simp = numerator();
	denominator_simp = denominator() * div;

	normalize(numerator_simp,denominator_simp);

	return *this;
}


// ratio == ratio
bool Ratio::operator==(const Ratio &eqOp) const{

	return this->ratio() == eqOp.ratio();
}


// ratio == number
bool Ratio::operator==(const long double ld) const{

	return this->ratio() == ld;
}


// number == ratio
bool operator==(const long double ld, const Ratio &eqOp){

	return ld == eqOp.ratio();
}


// ratio != ratio
bool Ratio::operator!=(const Ratio &notEq) const{

	return this->ratio() != notEq.ratio();
}


// ratio != number
bool Ratio::operator!=(const long double ld) const{

	return this->ratio() != ld;
}


// number != ratio
bool operator!=(const long double ld, const Ratio &notEq){

	return ld != notEq.ratio();
}


// ratio < ratio
bool Ratio::operator<(const Ratio &less) const{

	return this->ratio() < less.ratio();
}


// ratio < number
bool Ratio::operator<(const long double ld) const{

	return this->ratio() < ld;
}


// number < ratio
bool operator<(const long double ld, const Ratio &less) {

	return ld < less.ratio();
}


// ratio <= ratio
bool Ratio::operator<=(const Ratio &lessEq) const{

	return this->ratio() <= lessEq.ratio();
}


// ratio <= number
bool Ratio::operator<=(const long double ld) const{

	return this->ratio() <= ld;
}


// number <= ratio
bool operator<=(const long double ld, const Ratio &lessEq) {

	return ld <= lessEq.ratio();
}


// ratio > ratio
bool Ratio::operator>(const Ratio &greater) const{

	return this->ratio() > greater.ratio();
}


// ratio > number
bool Ratio::operator>(const long double ld) const{

	return this->ratio() > ld;
}


// number > ratio
bool operator>(const long double ld, const Ratio &greater) {

	return ld > greater.ratio();
}


// ratio >= ratio
bool Ratio::operator>=(const Ratio &greaterEq) const{

    return this->ratio() >= greaterEq.ratio();

}

// ratio >= number
bool Ratio::operator>=(const long double ld) const{

	return this->ratio() >= ld;
}

// number >= ratio
bool operator>=(const long double ld, const Ratio &greaterEq) {

        return ld >= greaterEq.ratio();
}


ostream &operator<<(ostream &stream, Ratio &value){

    return stream << value.numerator() << '/' << value.denominator();
}

istream &operator>>(istream &stream, Ratio &r){

    char div;
    long int top, bottom;

    stream >> top >> div >> bottom;

    if(div == '/' && top != ' ' && top != '\n' && bottom != ' ' && bottom != '\n'){
        Ratio nice(top,bottom);
        r = nice;
    }

    else{
        stream.setstate(ios_base::failbit);
    }
    return stream;
}