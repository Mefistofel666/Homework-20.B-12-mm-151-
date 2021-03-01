// Написать программу, выписывающую первые N простых чисел. Решето Эратосфена можно считать эффективным алгоритмом.
// Оценить сложность решения.
// O(n*ln(ln(n)))
#include <iostream>
using namespace std;
int main()
{
    int n, k = 2;
    cin >> n;
    while (n)
    {
        n--;
        cout << k << ' ';
        bool flag = true;
        while (flag)
        {
            flag = false;
            k++;
            int s = k / 2;
            for (int j = 2; j <= s; j++)
            {
                if (k % j == 0)
                {
                    flag = true;
                    break;
                }
            }
        }
    }
    return 0;
}