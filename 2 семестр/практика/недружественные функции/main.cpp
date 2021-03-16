#include <iostream>

class A
{
private:
    int a;
    double b;
    char c;
    long long d;

public:
    A(int x, double y, char t, long long z) : a(x), b(y), c(t), d(z){};
    friend std::ostream &operator<<(std::ostream &os, const A &cls)
    {
        return os << "a = " << cls.a << ", b = " << cls.b << ", c = " << cls.c << ", d = " << cls.d;
    }
};

class B
{
public:
    int a1;
    double b1;
    char c1;
    long long d1;

    B(int x, double y, char t, long long z) : a1(x), b1(y), c1(t), d1(z){};
};

int &get_a(A &x)
{
    return ((B *)(&x))->a1 = -42;
}

int main()
{
    int x = 10;
    double y = 0.5;
    char t = 'c';
    long long z = 10000;
    A example(x, y, t, z);
    int &ah = get_a(example);

    std::cout << ah << std::endl;
    ah = -5;

    std::cout << example;

    return 0;
}