#include <iostream>
#include "qsort.h"

using std::cin;
using std::cout;



int main(){
    int n;
    cin >> n;
    std::vector<int> A(n);
    for(size_t i = 0; i < n; i++){
        cin >> A[i];
    }
    quicksort(A, 0, n-1);
    for(size_t i = 0; i < n; i++){
        cout << A[i] << ' ';
    }

    return 0;
}