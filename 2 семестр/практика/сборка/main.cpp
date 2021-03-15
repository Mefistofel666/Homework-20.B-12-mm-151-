#include <iostream>
#include "mylib.h"
#include <vector>

using std::vector;

void display(vector<int> X){
    for(size_t i = 0; i < X.size(); i++){
        std::cout << X[i] << " ";
    }
}

int main(){

    int n;
    std::cin >> n;

    vector<int> A(n);


    for(size_t i = 0; i < n; i++){
        std::cin >> A[i];
    }

    vector<int> B = A;
    vector<int> C = A;

    MergeSort(A, 0, n-1); //сортировка

    quickSort(B,0, n-1);

    insertion_sort(C);


    display(A);
    std::cout << "\n";
    display(B);
    std::cout << "\n";
    display(C);
    


    return 0;
}