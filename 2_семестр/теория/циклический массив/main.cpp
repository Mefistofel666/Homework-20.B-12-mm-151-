#include <iostream>
#include "LoopArray.h"

int main()
{
    int n;
    std::cin >> n;

    LoopArray example(n);
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> example[i];
    }
    std::cout << example << "\n";

    example[n + 5] = 42;
    std::cout << example << "\n";

    return 0;
}