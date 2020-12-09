#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

// Вводится натуральное число

// Выводится его разложения на натуральные числа, являющиеся полными квадратами, с наименьшим числом слагаемых

struct qdr
{
    double len;
    vector<double> v;

    qdr()
    {
        len = 4;
        v = {};
    }
};
int main()
{
    double n;
    cin >> n;
    vector<qdr> vec(n + 1);
    for (double i = 0; i <= n; i++)
    {
        vec[i] = qdr();
        if (i == 1)
        {
            vec[i].len = 1;
            vec[i].v.push_back(1);
        }
        else if (i == 2)
        {
            vec[i].len = 2;
            vec[i].v.push_back(1);
            vec[i].v.push_back(1);
        }
        else if (i == 0)
        {
            vec[i].len = 1111111111111;
            vec[i].v.push_back(1);
        }
        else if (sqrt(i) == round(sqrt(i)))
        {
            vec[i].len = 1;
            vec[i].v.push_back(sqrt(i));
        }
        else
        {
            int j = 1;
            while (j * j <= i)
            {
                if (vec[i].len == 2)
                {
                    break;
                }
                if (vec[i].len > vec[i - j * j].len + 1)
                {
                    vec[i].len = vec[i - j * j].len + 1;
                    vec[i].v = {};
                    vec[i].v = vec[i - j * j].v;
                    vec[i].v.push_back(j);
                }
                j++;
            }
        }
    }

    cout << n << " = ";
    for (int j = 0; j < vec[n].len; j++)
    {
        cout << vec[n].v[j] << "^2 ";
        if (j < vec[n].len - 1)
            cout << "+ ";
    }

    return 0;
}
