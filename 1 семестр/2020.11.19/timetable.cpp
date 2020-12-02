#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

//Дана аудитория и k человек желающих читать в ней в лекции. Каждый человек указывает время лекции со времени a_i до b_i. Организовать расписание, при котором наибольшее количество занятий будет проведено.

//Вводится количество человек, потом время в формате int начала и конца лекции
//Выводится наилучшее расписание

int del(vector<pair<int, int>> v, int count)
{
    if (v.size() == 1)
    {
        cout << v[0].first << " " << v[0].second << "\n";
        return count + 1;
    }
    if (v[1].first <= v[0].second)
    {
        if (v[1].second <= v[0].second)
        {
            v.erase(v.begin());
            return del(v, count);
        }
        else
        {
            v.erase(v.begin() + 1);
            return del(v, count);
        }
    }
    else
    {
        cout << v[0].first << " " << v[0].second << "\n";
        v.erase(v.begin());
        return del(v, count + 1);
    }
}

bool cmp(pair<int, int> x, pair<int, int> y)
{
    if (x.first == y.first)
        return x.second > y.second;
    return x.first < y.first;
}

int main()
{

    int n;
    cin >> n;

    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; i++)
        cin >> vec[i].first >> vec[i].second;
    sort(vec.begin(), vec.end(), cmp);

    int res = del(vec, 0);

    return 0;
}