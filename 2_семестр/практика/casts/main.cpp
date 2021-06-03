#include <iostream>

int func(int *ptr)
{
    return (*ptr + 15);
}


class B { };
class C : public B { };
class D : public C { };

void f(D* pd)
{
   C* pc = dynamic_cast<C*>(pd);                  
   B* pb = dynamic_cast<B*>(pd);   
}

int main()
{
    // static_cast
    // 98, вместо "b"
    char a = 98;
    std::cout << static_cast<int>(a) << "\n";

    // const_cast
    // expected: 25
    const int val = 10;
    const int *ptr = &val;
    int *ptr1  = const_cast<int *> (ptr);
    std::cout << func(ptr1);

    // reinterpret_cast
     int* p = new int(65);
    char* ch = reinterpret_cast<char*>(p);
    std::cout << *p << std::endl;
    std::cout << *ch << std::endl;
    std::cout << p << std::endl;
    std::cout << ch << std::endl;

    // dynamic_cast


    return 0;
}