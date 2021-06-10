#include <iostream>
#include <vector>

template <typename T>
void swap(T& a, T& b)
{
  T c = a;
  a = b;
  b = c;
}

template <typename T>
void makeHeap(T*& arr, int n, int i)
{
    int max = i;    
    int left = 2*i + 1; 
    int right = 2*i + 2; 
 
    if (left < n && arr[left] > arr[max])
        max = left;
 
    if (right < n && arr[right] > arr[max])
        max = right;
 
    if (max != i)
    {
        swap(arr[i], arr[max]); 
        makeHeap(arr, n, max);
    }
}

template <typename T>
void heapSort(T*& arr, int n)
{ 
    for (int i = n / 2 - 1; i >= 0; i--)
        makeHeap(arr, n, i);
 
    for (int i = n - 1; i >= 0; i--)
    { 
        swap(arr[0], arr[i]); 
        makeHeap(arr, i, 0);
    }
} 


int main()
{

    int *arr = new int[5];
    for(int i = 0; i < 5; i++)
    {
        arr[i] = 5-i;
    }
    std::cout << "Before:\n";
    for(int i = 0; i < 5; i++)
    {
        std::cout << arr[i] << " ";
    }
    heapSort<int>(arr, 5);
    std::cout << "\nAfter:\n";

    for(int i = 0; i < 5; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}