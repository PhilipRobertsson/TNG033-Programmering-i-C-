/*********************************************
 * Lab 3: exercise 3                         *
 * Program to compute an approximation of PI *
 *********************************************/

#include <iostream>
#include <cmath>
#include <format>
#include <vector>

double calculate(double k) {
    double const factor{8.0 * k};
    double const init{4.0 / (factor + 1.0) - 1.0 / (factor + 4.0)};

   std::vector<double> other_factors{4.0, 5.0, 6.0};

    for (int i = 0; i < std::ssize(other_factors); ++i) {
       other_factors[i] = -1.0 / (factor + other_factors[i]);
    }

    double result{init};
    for (int i = 0; i < std::ssize(other_factors); ++i) {
        result += other_factors[i];
    }
    return result;
}

int main() {
    std::cout << "Enter number of terms: ";
    int n;
    std::cin >> n;

   std::vector<double> terms;

    for (int i = 0; i < n; ++i) {
        terms.push_back(i);
    }

    std::vector<double> power_terms{terms};

    for (int i = 0; i < std::ssize(terms); ++i) {
        terms[i] = calculate(terms[i]);
    }

    for (int i = 0; i < std::ssize(terms); ++i) {
        power_terms[i] = std::pow(16.0, -power_terms[i]);
    }

    double result{0.0};
    for (int i = 0; i < std::ssize(terms); ++i) {
        result += terms[i] * power_terms[i];
    }
    std::cout << std::format("{:.15f}\n", result);
}
