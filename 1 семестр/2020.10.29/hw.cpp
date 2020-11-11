#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector <int> vec(n);
    for (int i = 0; i < n; i++) cin >> vec[i];

    int start = 0, end = 1, res = 1;
    while (start < n){
        if (vec[end] > vec[end-1]) end++;
        else{
            if (res < end-start) res = end - start-1;
            start++;
            end = start + 1;
        }
    }
    cout << "res:" << res;

    return 0;

}
