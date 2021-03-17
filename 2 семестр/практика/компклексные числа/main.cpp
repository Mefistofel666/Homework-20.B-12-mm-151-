#include <iostream>
#include <cmath>
#include "complex.h"
// class Complex
// {
// public:
//     Complex(double x, double y) : real(x), im(y){};
//     friend Complex operator+(Complex &x, Complex &y);
//     friend Complex operator-(Complex &x, Complex &y);
//     friend Complex operator*(Complex &x, Complex &y);
//     friend Complex operator/(Complex &x, Complex &y);
//     Complex conjugate();
//     double module();
//     friend std::ostream &operator<<(std::ostream &os, const Complex &cls);

// private:
//     double real;
//     double im;
// };

// Complex operator+(Complex &x, Complex &y)
// {
//     return Complex(x.real + y.real, x.im + y.im);
// }
// Complex operator-(Complex &x, Complex &y)
// {
//     return Complex(x.real - y.real, x.im - y.im);
// }

// std::ostream &operator<<(std::ostream &os, const Complex &cls)
// {
//     return os << "Real = " << cls.real << ", Im = " << cls.im << "\n";
// }

// // (a+bi)(c+di) = ac-bd + i(ad+bc)
// Complex operator*(Complex &x, Complex &y)
// {
//     return Complex(x.real * y.real - x.im * y.im, x.real * y.im + x.im * y.real);
// }

// Complex Complex::conjugate()
// {
//     return Complex(real, - im);
// }

// double Complex::module()
// {
//     return pow(im*im + real*real, 1 / 2);
// }

// Complex operator/(Complex &x, Complex &y)
// {
//     Complex tmp = x * y.conjugate();
//     tmp.real = tmp.real / y.module();
//     tmp.im = tmp.im / y.module();
//     return Complex(tmp.real, tmp.im);
// }

int main()
{
    Complex a(10, 5);
    Complex b(5, 10);
    Complex d = a + b;
    Complex c = a - b;
    Complex z = c.conjugate();
    double z_mod = z.module();
    std::cout << "c: " << c << "d: " << d << "z: "<< z;
    std::cout << "|z| = " << z_mod <<"\n";
    std::cout << "|a| = " << a.module() << "\n";
    std::cout << "|b| = " << b.module() << "\n";

    return 0;
}