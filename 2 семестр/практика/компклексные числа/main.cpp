#include <iostream>
#include <cmath>
#include "complex.h"
#include <fstream>


int main()
{

    double x1, y1, x2, y2;
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;



    Complex a(x1, y1);
    Complex b(x2, y2);
    Complex c = a - b;
    Complex d = a + b;
    
    double mod_a = a.module();
    double mod_b = b.module();



    std::ofstream out;
    out.open("test_out.txt");

    if(out.is_open()){
        out << c << " " << d << " " << mod_a << " "<< mod_b;
    }


    // std::cout << "Sum of two complex numbers: " << d << "Difference of two complex numbers: " << c;
    // std::cout << "|a| = " << a.module() << "\n";
    // std::cout << "|b| = " << b.module() << "\n";

    return 0;
}