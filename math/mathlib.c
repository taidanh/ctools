#include "mathlib.h"

#include <math.h>
#include <stdio.h>

#define EPSILON 1e-14

double Abs(double x) {
    // eugene's section
    return x < 0 ? -x : x;
}

double Sin(double x) {
    // eugene's section
    x = fmod(x, 2 * M_PI);
    double num = x;
    double den = 1.0;
    double sum = num / den;
    double term = num / den; // term is the O(x^14) to check err
    for (double k = 3.0; Abs(term) > EPSILON; k += 2) {
        num *= -x * x;
        den *= (k - 1) * k;
        term = num / den;
        sum += num / den;
    }
    return sum;
}

double Cos(double x) {
    x = fmod(x, 2 * M_PI);
    double num = 1.0;
    double den = 1.0;
    double sum = num / den;
    double term = num / den;

    for (double k = 2.0; Abs(term) > EPSILON; k += 2) {
        num *= -x * x;
        den *= (k - 1) * k;
        term = num / den;
        sum += num / den;
    }
    return sum;
}

double Tan(double x) {
    x = fmod(x, M_PI / 2);
    return Sin(x) / Cos(x);
}

double Exp(double x) {
    // eugene's section
    double term = 1.0;
    double sum = term;
    for (double k = 1.0; Abs(term) > EPSILON; k += 1.0) {
        term = (x / k) * term;
        sum += term;
    }
    return sum;
}

double Log(double x) {
    double current = 1.0;
    double inv = Exp(current);
    while (Abs(inv - x) > EPSILON) {
        current += x / inv - 1;
        inv = Exp(current);
    }
    return current;
}
