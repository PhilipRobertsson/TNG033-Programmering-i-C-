/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"

// Polynomial constructor with double
Polynomial::Polynomial(double x) {
	Coeff.push_back(x);
}

// Polynomial constructor with vector
Polynomial::Polynomial(const std::vector<double>& V) {
	for (double D : V) {
		Coeff.push_back(D);
	}
}

// Polynomial constructor with polynomial (deep copy constructor)
Polynomial::Polynomial(const Polynomial& P) {
	for (int i = 0; i < std::ssize(P.Coeff); i++) {
		this->Coeff.push_back(P.Coeff[i]);
	}
}

// Clone function
Polynomial* Polynomial::clone() const {
	return new Polynomial{ *this };

}

// Returns Coeff with place x and can change it's place
double& Polynomial::operator[](int x) {
	return Coeff[x];
}

// Returns Coeff with place x but can't change it's place
const double& Polynomial::operator[](int x) const{
	return Coeff[x];
}

double Polynomial::operator()(double d) const {
	double temp = 0;
	for (int i = 0; i < std::ssize(Coeff); i++) {
		if (i == 0) {
			temp = Coeff[i];
		}
		else {
			temp += (Coeff[i] * pow(d, i));
		}
	} return temp;
}

Polynomial& Polynomial::operator+=(const Polynomial& P) {
	std::vector<double> newPol;

	for (int i = 0; i < std::ssize(P.Coeff); i++) {
		if (i < std::ssize(Coeff)) {
			newPol.push_back(operator[](i) + P[i]);
		}
		else {
			newPol.push_back(P[i]);
		}
	}
	if (std::ssize(Coeff) > std::ssize(P.Coeff)) {
		for (int i = std::ssize(P.Coeff); i < Coeff.size(); i++) {
			newPol.push_back(operator[](i));
		}
	}
	Polynomial temp{ newPol };
	*this = temp;
	return *this;
}

Polynomial operator+(Polynomial lhs, const Polynomial P) {
	lhs += P;
	return lhs;
}

void Polynomial::display(std::ostream& os) const {
	os << std::fixed << std::setprecision(2);
	for (int i = 0; i < std::ssize(Coeff); i++) {
		if (i == 0) {
			os << Coeff[i];
		}
		else if (Coeff[i] < 0) {
			os << " - " << abs(Coeff[i]) << " * X^" << i;
		}
		else {
			os << " + " << Coeff[i] << " * X^" << i;
		}
	}
}