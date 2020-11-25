#include <iostream>
#include <vector>
using namespace std;
// Выбрать все простые элементы из массива натуральных чисел не превосходящих k:
int main()
{
    vector<int> A = {1, 2, 3, 4, 5, 20, 7, 79, 9, 21, 29, 23, 43};
    int max = 0;

    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] > max)
            max = A[i];
    }
    vector<int> prime(max + 1);
    for (int i = 0; i <= max; i++)
    {
        prime[i] = 1;
    }

    prime[0] = prime[1] = 0;
    for (int i = 2; i <= max; ++i)
        if (prime[i] == 1)
            if (i * i <= max)
                for (int j = i * i; j <= max; j += i)
                    prime[j] = 0;
    vector<int> B;
    for (int i = 0; i <= max; i++)
    {
        if (prime[i] == 1)
        {
            B.push_back(i);
        }
    }

    for (int i = 0; i < A.size(); i++)
    {
        bool flag = false;
        int key = A[i];
        int l = 0, r = B.size();
        int mid;
        while ((l <= r) && (flag != true))
        {
            mid = (l + r) / 2;
            if (B[mid] == key)
                flag = true;
            if (B[mid] > key)
                r = mid - 1;
            else
                l = mid + 1;
        }
        if (flag)
            cout << A[i] << " ";
    }

    return 0;
}