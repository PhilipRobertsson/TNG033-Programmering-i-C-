/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "logarithm.h"
#include "polynomial.h"
#include <cmath>

// Create new logarith (default constructor)
Logarithm::Logarithm() :b(2), c1(0), c2(1) {
	std::vector<double> temp{ 0, 1 };
	E = new Polynomial{ temp };
}
// Copy constructor
Logarithm::Logarithm(const Logarithm& L) : b(L.b), c1(L.c1), c2(L.c2) {
	E = L.E->clone();
}
// Create logarithms
Logarithm::Logarithm(const Expression& Exp, double firstC, double secC, int base) : b(base), c1(firstC), c2(secC) {
	E = Exp.clone();
}

// Deconsructor
Logarithm::~Logarithm() {
	delete E;
	b = 0;
	c1 = 0;
	c2 = 0;
}
int& Logarithm::set_base(int x) {
	return this->b = x;
}
Logarithm* Logarithm::clone() const {
	return new Logarithm(*this);
}
double Logarithm::operator()(double d) const {
	double temp = c1 + c2 * (log(E->operator()(d)) / log(b));
	return temp;
}

Logarithm& Logarithm::operator=(const Logarithm& L){
	b = L.b; c1 = L.c1; c2 = L.c2;
	delete E;
	E = L.E->clone();

	return *this;
}

void Logarithm::display(std::ostream& os) const {
	os << std::fixed << std::setprecision(2);
	os << c1;
	if (c2 < 0) {
		os << " - " << abs(c2) << " * Log_" << b << "( " << *E << " )";
	}
	else {
		os << " + " << abs(c2) << " * Log_" << b << "( " << *E << " )";
	}
}