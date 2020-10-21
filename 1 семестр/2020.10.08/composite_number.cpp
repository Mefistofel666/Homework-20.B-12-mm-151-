// Написать функцию записывающую в переданный массив все составные числа меньшие N. Решето Эратосфена можно считать эффективным алгоритмом.
#include <iostream>
using namespace std;

int main()
{
    int n, count = 0;
    cin >> n;
    int *b = new int[n];
    bool *a = new bool[n];
    for (int i; i < n; i++)
        a[i] = true;
    for (int i = 2; i < n; i++)
    {
        if (a[i])
        {
            for (int j = i; j < n; j += i)
                a[j] = false;
        }
        else
        {
            b[count] = i;
            count++;
        }
    }
    delete[] a;
    int *c = new int[count];
    for (int i = 0; i < count; i++)
        c[i] = b[i];
    delete[] b;
    for (int i = 0; i < count; i++)
        cout << c[i] << " ";
    return 0;
}