// Написать программу вычисляющую биномиальный коэффициент из n по k.
#include <iostream>
using namespace std;
int main()
{
  float n, k, res = 1;
  cout << "Write n, and after k \n";
  cin >> n >> k;
  for (int i = 0; i < k; i++)
  {
    res = res * (n - i) / (k - i);
  }
  cout << "result: " << res;
  return 0;
}