#ifndef RATIO_H_INCLUDED
#define RATIO_H_INCLUDED
#include <iostream>
class Ratio{

private:

    long numerator_simp, denominator_simp;
    static int count;

public:

    void normalize(long numerator, long denominator);

    // default constructor
    Ratio() = delete;

    // floating point constructors
    Ratio(float num) = delete;
    Ratio(double num) = delete;
    Ratio(long double num) = delete;

    // constructors that create ratio
    Ratio(long numerator, long denominator = 1);
    Ratio(int numerator, int denominator = 1);


    // copy constructor
    Ratio(const Ratio &);

    // assignment operator
    Ratio &operator=(const Ratio &);

    // destructor
    ~Ratio();

    // returns numerator
    long numerator () const;
    //sets the numerator
    void numerator(long top);


    // returns denominator as a long
    long denominator () const;
    // sets the denominator
    void denominator(long bottom);


    // returns a long double representing the fraction
    long double ratio() const;

	// add subtract muliply divide yields another Ratio returned by value
	Ratio operator+(const Ratio &right);
	Ratio operator+(const long add);

	Ratio operator-(const Ratio &right);
	Ratio operator-(const long sub);

	Ratio operator*(const Ratio &right);
	Ratio operator*(const long prod);

	Ratio operator/(const Ratio &right);
	Ratio operator/(const long div);

	// assignment operator combines the two operands and replaces left side
	const Ratio &operator+=(const Ratio &right);
	const Ratio &operator+=(const long add);

	const Ratio &operator-=(const Ratio &right);
	const Ratio &operator-=(const long sub);

	const Ratio &operator*=(const Ratio &right);
	const Ratio &operator*=(const long prod);

	const Ratio &operator/=(const Ratio &right);
	const Ratio &operator/=(const long div);

	// boolean operators
	bool operator==(const Ratio &right) const;
	bool operator==(const long double ld) const;

	bool operator!=(const Ratio &right) const;
	bool operator!=(const long double ld) const;

	bool operator<(const Ratio &right) const;
	bool operator<(const long double ld) const;

	bool operator<=(const Ratio &right) const;
	bool operator<=(const long double ld) const;

	bool operator>(const Ratio &right) const;
	bool operator>(const long double ld) const;

	bool operator>=(const Ratio &right) const;
	bool operator>=(const long double ld) const;
};

Ratio operator+(const long l, const Ratio &right);
Ratio operator-(const long l, const Ratio &right);
Ratio operator*(const long l, const Ratio &right);
Ratio operator/(const long l, const Ratio &right);

bool operator==(const long double ld, const Ratio &right);
bool operator!=(const long double ld, const Ratio &right);
bool operator<(const long double ld, const Ratio &right);
bool operator<=(const long double ld, const Ratio &right);
bool operator>(const long double ld, const Ratio &right);
bool operator>=(const long double ld, const Ratio &right);

// non-methods for ostream and istream
std::ostream &operator<<(std::ostream &, Ratio &);
std::istream &operator>>(std::istream &, Ratio &);

#endif /* RATIO_H_INCLUDED */