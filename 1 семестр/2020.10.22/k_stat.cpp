#include <iostream>
#include <vector>
using namespace std;

int partition(int left, int right, vector<int> &arr)
{
    int mid = (left + right) / 2;
    int i = left,
        j = right;
    while (i <= j)
    {
        while (arr[i] < arr[mid])
            i++;
        while (arr[j] > arr[mid])
            j--;
        if (i >= j)
            break;
        swap(arr[i++], arr[j--]);
    }
    return j;
}

int findOrderStat(vector<int> arr, int k)
{
    int left = 0,
        right = arr.size() - 1;
    while (true)
    {
        int mid = partition(left, right, arr);
        if (mid == k)
            return arr[mid];
        else if (k < mid)
            right = mid - 1;
        else
            left = mid + 1;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> a = {1, 5, 2, 7, 4, 3, 8, 9};
    cout << findOrderStat(a, 5);

    return 0;
}