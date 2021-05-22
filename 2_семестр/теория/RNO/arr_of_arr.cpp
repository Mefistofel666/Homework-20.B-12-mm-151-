#include <iostream>
#include <malloc.h>

class ArrOfArr
{
    size_t m;
    int **A;
    int *data;
public:
    ArrOfArr(int *arrayK, size_t _m);
    ~ArrOfArr();
    ArrOfArr(const ArrOfArr &A);
    const ArrOfArr operator=(const ArrOfArr &A);
    int get(size_t i, size_t j);
    void put(size_t i, size_t j, int value);
};

ArrOfArr::ArrOfArr(int *arrayK, size_t _m):m(_m), A(new int*[m])
{
    size_t size = 0;
    for(int i = 0; i < m; i++)
    {
        size += arrayK[i];
    }
    data = new int[size];
    int tmp = 0;
    for(int i = 0; i < m; i++)
    {
        A[i] = data + tmp;
        tmp += arrayK[i];
    }
}
ArrOfArr::~ArrOfArr()
{
    for(size_t i = 0; i < m; i++)
    {
        delete A[i];
    }
    delete[] A;
    delete[] data; 
}

const ArrOfArr ArrOfArr::operator=(const ArrOfArr &_A)
{
    for(size_t i = 0; i < m; i++)
    {
        delete[] A[i];
    }
    m = _A.m;
    A = new int*[m];
    for(size_t i = 0; i < m; i++)
    {
        for(size_t j = 0; j < m; j++)
        {
            A[i][j] = _A.A[i][j];
        }
    }
    delete[] data;
    int length = sizeof(_A.data)/sizeof(int);
    data = new int[length];
    for(int i = 0; i < length;i++)
    {
        data[i] = _A.data[i];
    }

}
int ArrOfArr::get(size_t i, size_t j)
{
    try
    {
        if(i >= m) throw "Out of m ";
        if(j >= (size_t)(A[i] - A[i+1])) throw "Out of k[i] ";
        return A[i][j];
    }
    catch(const char *exception)
    {
        std::cerr <<"Error: " << exception << '\n';
        return -1;
    }
}
void ArrOfArr::put(size_t i, size_t j, int value)
{
    try
    {
        if(i >= m) throw "Out of m ";
        if(j >= (size_t)(A[i] - A[i+1])) throw "Out of k[i] ";
        A[i][j] = value;
    }
    catch(const char *exception)
    {
        std::cerr <<"Error: " << exception << '\n';
    }
}



int main() {
    int *A = new int[10];
    for (int i = 0; i < 10; i++)
        A[i] = i + 4;
    size_t size = 10;
    ArrOfArr B(A, size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < A[i]; j++) 
            B.put(i, j, (i+j) % 2 );

    for (int i = 0; i < size; i++)
    {
        std::cout <<"Size = " << A[i] << "-> ";
        for (int j = 0; j < A[i]; j++)
            std::cout << B.get(i, j) << " ";
        std::cout << "\n";
    }

    return 0;
}