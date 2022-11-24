/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

#include "expression.h"

class Logarithm : public Expression {
public:
	Logarithm(); // Default constructor

	Logarithm(const Logarithm& L); // Copy constructor

	Logarithm(const Expression& Exp, double firstC, double secC, int base);

	~Logarithm();

	int& set_base(int x);

	Logarithm* clone() const override;

	virtual double operator()(double d) const override;
	Logarithm& operator=(const Logarithm& L);
private:
	double c1, c2;
	int b;
	Expression* E;

	void display(std::ostream& os = std::cout) const override;
};
