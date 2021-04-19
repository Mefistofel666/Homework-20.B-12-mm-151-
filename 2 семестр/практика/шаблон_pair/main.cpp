#include <iostream>

#include "Pair.h"


int main()
{
    pair<int, char> A(5, 'c');
    pair<int, char> B(6, 'd');
    auto C = pair<int, char>(B);

    std::cout << "BEFORE: " << std::endl;
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;

    std::cout << "AFTER:"  << std::endl;

    A.Swap(B);

    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;





    return 0;
}