/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "expression.h"

class Polynomial : public Expression {
public:
	//Conversion constructor
	Polynomial(double x);
	//Constructor with vector
	explicit Polynomial(const std::vector<double>& V);
	//copy
	Polynomial(const Polynomial& P);

	Polynomial* clone() const override;

	//Assignment operator
	Polynomial& operator=(const Polynomial&) = default;

	//Operators
	virtual double operator()(double d) const override;
	double& operator[](int x);
	const double& operator[](int x) const;
	Polynomial& operator+=(const Polynomial& P);
	friend Polynomial operator+(Polynomial lhs, const Polynomial P);

private:
	void display(std::ostream& os = std::cout) const override;
	std::vector<double> Coeff;
};
