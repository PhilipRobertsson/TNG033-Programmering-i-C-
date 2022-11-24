/******************************************************
 * Test program for the expressions hierarchy          *
 * TNG033: Lab 2                                       *
 *******************************************************/

#include <iostream>
#include <format>
#include <vector>
#include <sstream>
#include <cassert>

#include "polynomial.h"
#include "logarithm.h"

int main() {
    /*****************************************************
     * TEST PHASE 0                                       *
     * Polynomial: conversion constructor and operator<<  *
     ******************************************************/
    std::cout << "TEST PHASE 0: Polynomial - conversion constructor and operator<<\n";

    {
        Polynomial p1{6.6};  // conversion constructor: convert a double to a Polynomial

        // Test
        std::ostringstream os{};
        os << "p1 = " << p1;

        std::string tmp{os.str()};
        assert((tmp == std::string{"p1 = 6.60"}));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 1                                       *
     * Polynomial: constructors and operator<<            *
     ******************************************************/
    std::cout << "\nTEST PHASE 1: Polynomial - constructors and operator<<\n";

    {
        std::vector<double> v1{2.2, 4.4, -2.0, 5.0};
        const Polynomial p1{v1};  // create a polynomial of degree 3

        // Test
        std::ostringstream os{};
        os << "p1 = " << p1;

        std::string tmp{os.str()};
        assert((tmp == std::string{"p1 = 2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"}));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 2                                       *
     * Polynomial: operator[]                             *
     ******************************************************/
    std::cout << "\nTEST PHASE 2: Polynomial::operator[]\n";

    {
        std::vector<double> v1{2.2, 4.4, -2.0, 5.0};
        Polynomial p1{v1};  // create a polynomial of degree 3

        p1[2] = -8;
        // Test
        std::ostringstream os{};
        os << "p1 = " << p1;

        std::string tmp{os.str()};
        assert((tmp == std::string{"p1 = 2.20 + 4.40 * X^1 - 8.00 * X^2 + 5.00 * X^3"}));

        const Polynomial p2{v1};
        // p2[3] = -4.4; // should not compile

        assert(Expression::get_count_expressions() == 2);
        assert(p2[2] == -2.0);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 3                                       *
     * Polynomial: copy constructor                       *
     ******************************************************/
    std::cout << "\nTEST PHASE 3: Polynomial - copy constructor\n";

    {
        std::vector<double> v1{2.2, 4.4, -2.0, 5.0};
        Polynomial p1{v1};  // create a polynomial of degree 3

        Polynomial p2{p1};  // copy constructor

        assert(Expression::get_count_expressions() == 2);

        p1[2] = 0.0;  // should not modify p2

        // Test
        std::ostringstream os{};
        os << "p2 = " << p2;

        std::string tmp{os.str()};
        assert((tmp == std::string{"p2 = 2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"}));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 4                                       *
     * Polynomial: assignment operator                    *
     ******************************************************/
    std::cout << "\nTEST PHASE 4: Polynomial - assignment operator\n";

    {
        std::vector<double> v1{2.2, 4.4, -2.0, 5.0};
        Polynomial p1{v1};  // create a polynomial of degree 3

        p1 = p1;  // self-assignment
        // Test
        assert(Expression::get_count_expressions() == 1);
        std::ostringstream os1{};
        os1 << "p1 = " << p1;

        std::string tmp1{os1.str()};
        assert((tmp1 == std::string{"p1 = 2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"}));

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};

        Polynomial p3{6.6};

        p3 = p2 = p1;
        // Test
        assert(Expression::get_count_expressions() == 3);
        std::ostringstream os2{};
        os2 << "p2 = " << p2 << " p3 = " << p3;

        std::string tmp2{os2.str()};
        assert((tmp2 == std::string{"p2 = 2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3 "
                                    "p3 = 2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"}));

        p1[1] = -999.0;  // should not modify neither p3 nor p2

        // Test
        std::ostringstream os3{};
        os3 << "p2 = " << p2 << " p3 = " << p3;

        std::string tmp3{os3.str()};
        assert(tmp3 == tmp2);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 5                                       *
     * Polynomial: operator()                             *
     ******************************************************/
    std::cout << "\nTEST PHASE 5: Polynomial::operator()\n";

    {
        std::vector<double> v1{-1, 0, 1};
        Polynomial p1{v1};

        assert(p1(1) == 0.0);

        std::vector<double> v2{2.2, 4.4, 2.0, 5.0};
        const Polynomial p2{v2};  // create a polynomial of degree 3

        // Test
        std::ostringstream os{};
        os << std::format("{:.2f}", p2(3.3));

        std::string tmp{os.str()};
        assert(tmp == "218.19");
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 6                                       *
     * Polynomial: isRoot                                 *
     ******************************************************/
    std::cout << "\nTEST PHASE 6: Polynomial::isRoot\n";

    {
        std::vector<double> v1{-1, 0, 1};
        Polynomial p1{v1};

        assert(p1.isRoot(1));

        std::vector<double> v2{2.2, 4.4, 2.0, 5.0};
        const Polynomial p2{v2};

        assert(p2.isRoot(1) == false);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 7                                       *
     * Polynomial: P1 += P2                                  *
     ******************************************************/
    std::cout << "\nTEST PHASE 7: P1 += P2\n";

    {
        std::vector<double> v1{2.2, 4.4, 2.0, 5.0};
        Polynomial p1{v1};  // create a polynomial of degree 3

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};  // create a polynomial of degree 2

        p1 += p2;
        // Test
        assert(Expression::get_count_expressions() == 2);
        std::ostringstream os1{};
        os1 << "p1 = " << p1;

        std::string tmp1{os1.str()};
        assert((tmp1 == std::string{"p1 = 1.20 + 4.40 * X^1 + 3.00 * X^2 + 5.00 * X^3"}));

        p2 += p1;
        assert(Expression::get_count_expressions() == 2);
        // Test
        std::ostringstream os2{};
        os2 << "p2 = " << p2;

        std::string tmp2{os2.str()};
        assert((tmp2 == std::string{"p2 = 0.20 + 4.40 * X^1 + 4.00 * X^2 + 5.00 * X^3"}));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 8                                       *
     * Polynomial: P1+P2                                  *
     ******************************************************/
    std::cout << "\nTEST PHASE 8: P1 + P2\n";

    {
        std::vector<double> v1{2.2, 4.4, 2.0, 5.0};
        const Polynomial p1{v1};  // create a polynomial of degree 3

        std::vector<double> v2{2.2, 4.4, 2.0};
        const Polynomial p2{v2};  // create a polynomial of degree 2

        std::vector<double> v3{-1, 0, 1};
        Polynomial p3{v3};  // create a polynomial of degree 2

        // Test
        std::ostringstream os1{};
        os1 << "p1 + p2 = " << p1 + p2;

        std::string tmp1{os1.str()};
        assert((tmp1 == std::string{"p1 + p2 = 4.40 + 8.80 * X^1 + 4.00 * X^2 + 5.00 * X^3"}));

        Polynomial p4 = p1 + p2 + p3;

        // Test
        assert(Expression::get_count_expressions() == 4);
        std::ostringstream os2{};
        os2 << "p4 = " << p4;

        std::string tmp2{os2.str()};
        assert((tmp2 == std::string{"p4 = 3.40 + 8.80 * X^1 + 5.00 * X^2 + 5.00 * X^3"}));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 9                                       *
     * Polynomial: p += k, k+P and P+k                    *
     ******************************************************/
    std::cout << "\nTEST PHASE 9: p += k, k+P and P+k\n";

    {
        std::vector<double> v1{4.40, 8.80, 4.00, 5.00};
        Polynomial p1{v1};  // create a polynomial of degree 3

        p1 += 2.0;
        // Test
        std::ostringstream os1{};
        os1 << "p1 = " << p1;

        std::string tmp1{os1.str()};
        assert((tmp1 == std::string{"p1 = 6.40 + 8.80 * X^1 + 4.00 * X^2 + 5.00 * X^3"}));

        p1 = 0.0 + p1 + 3.3;
        // Test
        assert(Expression::get_count_expressions() == 1);
        std::ostringstream os2{};
        os2 << "p1 = " << p1;

        std::string tmp2{os2.str()};
        assert((tmp2 == std::string{"p1 = 9.70 + 8.80 * X^1 + 4.00 * X^2 + 5.00 * X^3"}));

        std::vector<double> v2{1.2, 4.4, 2.0, 0.0, 3.1, 6.6};
        const Polynomial p2{v2};  // create a polynomial of degree 5

        p1 += (0.0 + p2);
        // Test
        assert(Expression::get_count_expressions() == 2);
        std::ostringstream os3{};
        os3 << "p1 = " << p1;

        std::string tmp3{os3.str()};
        assert(
            (tmp3 ==
             std::string{
                 "p1 = 10.90 + 13.20 * X^1 + 6.00 * X^2 + 5.00 * X^3 + 3.10 * X^4 + 6.60 * X^5"}));
    }

    assert(Expression::get_count_expressions() == 0);

    /******************************************************
     * TEST PHASE 10                                       *
     * Logarithm: constructors, set_base, operator<<       *
     ******************************************************/
    std::cout << "\nTEST PHASE 10: Logarithm - constructors, set_base, operator<<\n";

    {
        Logarithm l1;  // default constructor
        // Test
        assert(Expression::get_count_expressions() == 2);
        std::ostringstream os1{};
        os1 << "l1 = " << l1;

        std::string tmp1{os1.str()};
        assert((tmp1 == std::string{"l1 = 0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 )"}));

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};  // create a polynomial of degree 2

        Logarithm l2{p2, 2, -3, 10};
        // Test
        assert(Expression::get_count_expressions() == 5);
        std::ostringstream os2{};
        os2 << "l2 = " << l2;

        p2[1] = -999.0;  // should not modify  l2

        std::string tmp2{os2.str()};
        assert(tmp2 == std::string{"l2 = 2.00 - 3.00 * Log_10( -1.00 + 0.00 * X^1 + 1.00 * X^2 )"});

        Logarithm l3{l1, 1, 2, 10};

        assert(Expression::get_count_expressions() == 8);

        l1.set_base(3);  // should not modify l3

        // Test
        std::ostringstream os3{};
        os3 << "l3 = " << l3;

        std::string tmp3{os3.str()};
        assert(
            tmp3 ==
            std::string{"l3 = 1.00 + 2.00 * Log_10( 0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 ) )"});
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 11                                      *
     * Logarithm: copy constructor                        *
     ******************************************************/
    std::cout << "\nTEST PHASE 11: Logarithm - copy constructor\n";

    {
        Logarithm l1;  // default constructor
        assert(Expression::get_count_expressions() == 2);

        Logarithm* ptr_l2 = new Logarithm{l1, 1, 2, 10};
        assert(Expression::get_count_expressions() == 5);

        Logarithm l3{*ptr_l2};  // copy constructor
        assert(Expression::get_count_expressions() == 8);

        delete ptr_l2;  // should not affect l3
        ptr_l2 = nullptr;

        // Test
        std::ostringstream os{};
        os << "l3 = " << l3;

        std::string tmp{os.str()};
        assert(tmp == std::string(
                          "l3 = 1.00 + 2.00 * Log_10( 0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 ) )"));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 12                                      *
     * Logarithm: isRoot                                  *
     ******************************************************/
    std::cout << "\nTEST PHASE 12: isRoot\n";

    {
        const Logarithm l1;
        assert(Expression::get_count_expressions() == 2);
        assert(l1.isRoot(1));

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};  // create a polynomial of degree 2

        Logarithm l2{p2, 2, 3, 10};
        assert(Expression::get_count_expressions() == 5);
        assert(l2.isRoot(2) == false);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 13                                       *
     * Logarithm: operator()                              *
     ******************************************************/
    std::cout << "\nTEST PHASE 13: Logarithm::operator()\n";

    {
        const Logarithm l1;
        assert(Expression::get_count_expressions() == 2);
        assert(l1(1) == 0.0);

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};  // create a polynomial of degree 2

        Logarithm l2{p2, 2, 3, 10};
        assert(Expression::get_count_expressions() == 5);
        assert(l2(2) >= 3.4313);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 14                                      *
     * Logarithm: assignment operator                     *
     ******************************************************/
    std::cout << "\nTEST PHASE 14: Logarithm - assignment operator\n";

    {
        Logarithm l0;
        assert(Expression::get_count_expressions() == 2);

        std::vector<double> v1{-1, 0, 1};
        Polynomial p1{v1};  // create a polynomial of degree 2

        Logarithm* ptr_l1 = new Logarithm{p1, 1, 1, 2};
        assert(Expression::get_count_expressions() == 5);

        l0 = *ptr_l1;
        assert(Expression::get_count_expressions() == 5);

        delete ptr_l1;  // shoudld not affect l0
        ptr_l1 = nullptr;
        assert(Expression::get_count_expressions() == 3);

        // Test
        std::ostringstream os{};
        os << "l0 = " << l0;

        std::string tmp{os.str()};
        assert(tmp == std::string("l0 = 1.00 + 1.00 * Log_2( -1.00 + 0.00 * X^1 + 1.00 * X^2 )"));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 15                                      *
     * Expressions: polymorphism                          *
     ******************************************************/
    std::cout << "\nTEST PHASE 15:  Expressions - polymorphism\n";

    {
        std::vector<Expression*> V{new Logarithm{}, new Polynomial{std::vector<double>{-1, 0, 1}}};
        assert(Expression::get_count_expressions() == 3);

        for (auto e : V) {
            assert(e->isRoot(1));
            delete e;
        }
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 16                                      *
     * Expression: assignment                             *
     ******************************************************/

    std::cout << "\nTEST PHASE 16:  Expression::operator=\n";

    {
        std::vector<double> v1{-1, 0, 1};
        Expression* e1 = new Polynomial{v1};

        Expression* e2 = new Logarithm{};

       /* *e1 = *e2; //<-- should not compile!! */
       
    }

    std::cout << "\nSuccess!!\n";
}

