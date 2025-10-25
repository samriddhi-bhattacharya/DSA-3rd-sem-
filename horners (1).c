#include <stdio.h>
double horner(double coefficients[], int degree, double x) {
    if (degree == 0) {
        return coefficients[0];
    }
    return coefficients[degree] + x * horner(coefficients, degree - 1, x);
}

int main() {
    double coeffs[] = {-1, 2, -6, 2}; 
    int degree = sizeof(coeffs)/sizeof(coeffs[0]) - 1;
    double x = 3.0;
    
    double result = horner(coeffs, degree, x);
    
    printf("Evaluating polynomial at x = %.2f\n", x);
    printf("Result: %.2f\n", result);
    
    return 0;
}