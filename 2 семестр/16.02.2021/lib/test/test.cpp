#include <iostream>
#include <vector>
#include "mylib.h"

int main(){

    int n;
    std::cin>>n;
    std::vector<int> A(n);
    for(size_t i = 0; i < n; i++){
        std::cin>> A[i];
    }

    quicksort(A, 0, n-1);
    
    for(size_t i = 0; i < n; i++){
        std::cout << A[i] << " ";
    }

    return 0;
}