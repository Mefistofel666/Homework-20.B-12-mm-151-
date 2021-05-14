#include <iostream>
#include <vector>

using std::vector;

int amount = 0;
static void merge(vector<int> &buf, size_t left, size_t right, size_t middle) //слияние
{
  if (left >= right || middle < left || middle > right)
    return;
  if (right == left + 1 && buf[left] > buf[right])
  {
    std::swap(buf[left], buf[right]);
    amount++;
    return;
  }

  vector<int> tmp(&buf[left], &buf[right] + 1);

  for (size_t i = left, j = 0, k = middle - left + 1; i <= right; ++i)
  {
    if (j > middle - left)
    {
      buf[i] = tmp[k++];
    }
    else if (k > right - left)
    {
      buf[i] = tmp[j++];
    }
    else
    {
      buf[i] = (tmp[j] < tmp[k]) ? tmp[j++] : tmp[k++];
    }
  }
}

void MergeSort(vector<int> &buf, size_t left, size_t right) //сортировка
{
  if (left >= right)
    return;

  size_t middle = left + (right - left) / 2;

  MergeSort(buf, left, middle);
  MergeSort(buf, middle + 1, right);
  merge(buf, left, right, middle);
}
