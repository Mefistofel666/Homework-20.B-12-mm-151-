#include <iostream>
using namespace std;

int ackerman_func(int m, int n){
    if (m == 0) return n+1;
    else if(m>0 && n == 0) return ackerman_func(m-1, 1);
    else if (m>0 && n>0) return ackerman_func(m-1, ackerman_func(m,n-1));
    return 0;
}
int main(){
    int m,n;
    cin >> m >> n;
    int res = ackerman_func(n,m);
    cout << "res: " << res;
    return 0;
}