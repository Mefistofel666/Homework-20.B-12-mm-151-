// Написать программу находящую среднее арифметическое кубов последовательности чисел
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int n;
    float sum;
    cout << "Write n: ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        sum = sum + pow(i, 3);
    }
    cout << "average: " << sum / n;
    return 0;
}
