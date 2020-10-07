// Закончить и реализовать структуру Rational(с пары). В main привести примеры использования методов и функций.
#include <iostream>
#include <string>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return abs(gcd(b, a % b));
}
int lcm(int a, int b)
{
    return abs(a * b / gcd(a, b));
}
struct Rational
{
    int m;
    int n;
    Rational(int x, int y)
    {

        m = x / gcd(x, y);
        n = abs(y) / gcd(x, y);
    }
    string getFraction()
    {
        string res = "Answer: ";
        if (m != 0 && n != 0)
            return to_string(m) + "/" + to_string(n) + "\n";
        else if (m == 0)
            return "0\n";
        else
            return "Error: Division by zero!\n";
    }
    string getCorrectFraction()
    {
        int integer_part = m / n;
        int modulo = m % n;
        string res = to_string(integer_part) + " integer and " + to_string(modulo) + "/" + to_string(n) + "\n";
        return res;
    }

    Rational &operator*=(Rational &x)
    {
        m *= x.m;
        n *= x.n;
        int temp = gcd(m, n);
        n /= temp;
        m /= temp;
        return *this;
    }
    Rational &operator+=(Rational &x)
    {
        m = m * (lcm(n, x.n) / n) + x.m * (lcm(n, x.n) / x.n);
        n = lcm(n, x.n);
        int temp = gcd(m, n);
        n /= temp;
        m /= temp;
        return *this;
    }
    Rational &operator/=(Rational &x)
    {
        m *= x.n;
        n *= x.m;
        int temp = gcd(m, n);
        n /= temp;
        m /= temp;
        return *this;
    }
};

int main()
{
    Rational r1(-4, 7), r2(10, 15), r3(0, 1), r4(1, 0);
    cout << "first num: " << r1.getFraction();
    cout << "second num: " << r2.getFraction();
    cout << "third num: " << r3.getFraction();
    cout << "fourth num: " << r4.getFraction();

    cout << "Multiplication: " << r1.m << "/" << r1.n << " * " << r2.m << "/" << r2.n << " = ";
    r1 *= r2;
    cout << r1.getFraction();

    cout << "Summary: " << r1.m << "/" << r1.n << " + " << r2.m << "/" << r2.n << " = ";
    r1 += r2;
    cout << r1.getFraction();

    cout << "Division: " << r1.m << "/" << r1.n << " : " << r2.m << "/" << r2.n << " = ";
    r1 /= r2;
    cout << r1.getFraction();

    return 0;
}