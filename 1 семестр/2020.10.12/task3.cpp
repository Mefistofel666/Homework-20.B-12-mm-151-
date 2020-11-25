#include <iostream>

// Найти количество подмассивов с суммой элементов не превосходящих k в массиве натуральных чисел

using namespace std;

int main()
{
    int n, k, res{0};

    cin >> n;

    cin >> k;

    int *arr = new int[n];

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int count = 0, i = -1, sum = 0;

    while (i < n - 1)
    {
        i++;
        sum += arr[i];
        while ((sum > k) && (i > count))
        {
            sum -= arr[count];
            count++;
        }

        if (sum <= k)
            res += (count <= i) ? (i - count + 1) : 0;
    }

    cout << "\n"
         << res;
}