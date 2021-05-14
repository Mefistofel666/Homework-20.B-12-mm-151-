#include <iostream>
#include <vector>
#include "matrix.h"

int main()
{

    // --Tranpose--
    std::cout << "Transpose: \n";
    Matrix<int> M(5, 3);
    Matrix<int> N = M.transpose();
    std::cout << M;
    std:: cout << "\n";
    std::cout<< N;
   

    Matrix<int> C(2,3);
    for(int i = 0; i < 2;i++)
    {
        for(int j = 0; j < 3; j++)
        {
            C(i,j) = 3;
        }
    }
    Matrix<int> H(2,3);
    for(int i = 0; i < 2;i++)
    {
        for(int j = 0; j < 3; j++)
        {
            H(i,j) = 2;
        }
    }

    Matrix<int> D(3,2);
    for(int i = 0; i < 3;i++)
    {
        for(int j = 0; j < 2; j++)
        {
            D(i,j) = 2;
        }
    }
    Matrix<int> F(4,2);
    for(int i = 0; i < 3;i++)
    {
        for(int j = 0; j < 2; j++)
        {
            D(i,j) = 2;
        }
    }

    Matrix<int> E;

    // Sum of matrix
    E = C + H;
    std::cout << "Sum: \n"<< E;

    // Difference of matrices
    E = C - H;
    std::cout << "Difference: \n" << E;

    // Product of matrix
    E = C * D;
    std::cout << "Product: \n" << E;

    // Bad Product of matrix
    E = C * F;
    std::cout << "Bad Product: \n" << E;

   
    return 0;
}

   
