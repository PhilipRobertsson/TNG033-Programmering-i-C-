/*************************
 * Class Expression       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

constexpr double Epsilon = 1.0e-5;

class Expression {
public:
    // Destructor
    virtual ~Expression() {
        --count_expressions;
    }

    // ADD OTHER MEMBER FUNCTIONS
    bool isRoot(double x) const;

    virtual Expression* clone()const = 0;
    virtual double operator()(double d) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Expression& E);

    // Return number of existing instances of class Expression
    // Used only for debug purposes
    static std::size_t get_count_expressions();

protected:
    // Default constructor
    Expression() {
        ++count_expressions;
    }

    // Copy constructor
    Expression(const Expression&) {
        ++count_expressions;
    }

    // Total number of existing expressions -- to help to detect bugs in the code
    static std::size_t count_expressions;

    virtual void display(std::ostream& os = std::cout) const = 0;

    // Assignement opperator
    Expression& operator=(const Expression& E) = default;

};
