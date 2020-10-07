// Написать функцию сортировки массива, использующую указательную арифметику вместо обращения по индексам.
#include <iostream>
using namespace std;

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

void sort(int *A, int n)
{
    int *p = A;
    int *q = A + n;
    for (; p != q; p++)
    {
        int j = *p;
        for (; j != 0 && *(A + j - 1) > *(A + j); j--)
            swap(*(A + j - 1), *(A + j));
    };
}

int main()
{
    int n;
    cin >> n;
    int *A = new int[n];
    int *p = A;
    int *q = A + n;
    for (; p != q; p++)
        cin >> *p;
    p = A;
    sort(A, n);
    for (; p != q; p++)
    {
        cout << *p << " ";
    };
    return 0;
}