#include <iostream>
#include <vector>

using namespace std;

//Дана прямоугольная клетчатая карта, в ячейках которой указаны стоимости прохода по клетке. Из клетки ходить вниз, вправо и по диагонали вниз-вправо. Напишите программу, находящую самый дешевый путь из верхней левой в правую нижнюю клетку.

// Вводится n, m, массив n х m

//Выводится мимнмальная стоимость

int min(int x, int y, int z)
{
    if (x <= y && x <= z)
        return x;
    if (y <= z)
        return y;
    return z;
}

int main()
{
    int n, m, a;
    cin >> n >> m;

    vector<vector<int>> v(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            v[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a;
            v[i][j] = a;
        }
    }
    vector<vector<int>> Map(n, vector<int>(m));

    Map[0][0] = 0;
    for (int j = 1; j < m; j++)
        Map[0][j] = Map[0][j - 1] + v[0][j];
    for (int j = 1; j < n; j++)
        Map[j][0] = Map[j - 1][0] + v[j][0];

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            Map[i][j] = min(Map[i - 1][j], Map[i - 1][j - 1], Map[i][j - 1]) + v[i][j];
        }
    }

    cout << Map[n - 1][m - 1];
    return 0;
}