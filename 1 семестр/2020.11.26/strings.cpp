#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Даны два слова на алфавите {A,C,G,T}. Найти минимальное количество операций добавления,
// удаления и замены буквы необходимые для приведения слова A к B.

int min(int x, int y, int z)
{
    if (x < y && x < z)
        return x;
    else if (y < z)
        return y;
    else
        return z;
}

int costm(char x, char y)
{
    if (x == y)
        return 0;
    return 1;
}

int main()
{

    
    string s1, s2;
    int m, n;
    cin >> s1 >> s2;
    m = s1.length();
    n = s2.length();

    vector<vector<int>> D(m, vector<int>(n));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = 0;
        }
    }

    for (int i = 1; i < m; i++)
    {
        D[i][0] = D[i - 1][0] + 1;
    }
    for (int j = 1; j < n; j++)
    {
        D[0][j] = D[0][j - 1] + 1;
    }

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            D[i][j] = min(D[i - 1][j] + 1, D[i][j - 1] + 1, D[i - 1][j - 1] + costm(s1[i], s2[j]));
        }
    }  

    cout << D[m - 1][n - 1];
    return 0;
}