#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void swap_el(int &a, int &b){
  int temp = a;
  a = b;
  b = temp;
}

void quickSort(vector<int> &value, long long left, long long right)
{
  int mid = value[(left + right) / 2];
  long long i = left, j = right;
  do
  {
    while (value[i] < mid) 
      i++;
    while (value[j] > mid) 
      j--;
    if (i <= j){
      swap_el(value[i], value[j]);
      i++;
      j--;
    }
  }while (i <= j);
  if (j > left)
    quickSort(value,left, j);
  if (right > i)
    quickSort(value,i, right);
}