#include "std_lib_facilities.h"
#include "Q2.h"

int main() {
    // Problem 2-1 —— Bisection method
    vector<double> indexVec = {-4, 0, 1}; // stands for the function: f(x) = -4 + x^2
    double solution1 = BisectionMethod(indexVec, -6.0, 0.0);
    cout << "Bisection method solution is around: "<< solution1 << " according to Bisection method."<< endl;
    double solution1_2 = BisectionMethod(indexVec, 5, 0.0);
    cout << "Bisection method solution is around: "<< solution1_2 << " according to Bisection method."<< endl;

    // Problem 2-2 —— Secant method
    double solution2 = SecantMethod(indexVec , -6.0, 0.0);
    cout << "Secant method solution is around: "<< solution2 << " according to Secant method."<< endl;
    double solution2_2 = SecantMethod(indexVec , 0, 5.0);
    cout << "Secant method solution is around: "<< solution2_2 << " according to Secant method."<< endl;
}
