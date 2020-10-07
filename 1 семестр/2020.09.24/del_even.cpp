// Написать функцию удаляющую из целочисленного массива все четные элементы. Гарантируется, что в массиве есть хотя бы один нечетный элемент. После исполнения такой функции массив должен уменьшить свой размер.
#include <iostream>
using namespace std;

int main()
{
    const int N = 10;
    int *a = new int[N];
    int *even = new int[N];
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        if (a[i] % 2 == 0)
        {
            even[count] = a[i];
            count += 1;
        }
    }
    int *temp = new int[count];
    for (int i = 0; i < count; i++)
    {
        temp[i] = even[i];
        cout << temp[i] << " ";
    }
    delete even;
    delete a;
    even = temp;

    return 0;
}