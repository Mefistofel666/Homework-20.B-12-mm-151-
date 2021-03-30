#include <iostream>
#include "complex.h"
#include <cmath>
Complex operator+(Complex &x, Complex &y)
{
    return Complex(x.real + y.real, x.im + y.im);
}
Complex operator-(Complex &x, Complex &y)
{
    return Complex(x.real - y.real, x.im - y.im);
}

std::ostream &operator<<(std::ostream &os, const Complex &cls)
{
    return os << "Real = " << cls.real << ", Im = " << cls.im << "\n";
}

// (a+bi)(c+di) = ac-bd + i(ad+bc)
Complex operator*(Complex &x, Complex &y)
{
    return Complex(x.real * y.real - x.im * y.im, x.real * y.im + x.im * y.real);
}

Complex Complex::conjugate()
{
    return Complex(real, -im);
}

double Complex::module()
{
    return pow(im * im + real * real, 0.5);
}

Complex operator/(Complex &x, Complex &y)
{
    Complex tmpy = y.conjugate();
    Complex tmp = x * tmpy;
    tmp.real = tmp.real / y.module();
    tmp.im = tmp.im / y.module();
    return Complex(tmp.real, tmp.im);
}