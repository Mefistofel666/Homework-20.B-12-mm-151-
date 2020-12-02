#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct item
{
    int cost;
    int weight;
    float unit_cost;
    item(int x, int y)
    {
        cost = x;
        weight = y;
        unit_cost = x / y;
    }
};

bool sort_item(item x, item y)
{
    return x.unit_cost >= y.unit_cost;
}

int main()
{
    int n, w;
    cout << " write n: ";
    cin >> n;
    cout << " write w: ";
    cin >> w;

    vector<item> items;

    for (int i = 0; i < n; i++)
    {
        int cost_i, weight_i;
        cin >> cost_i >> weight_i;
        item item_i = item(cost_i, weight_i);
        items.push_back(item_i);
    }

    sort(items.begin(), items.end(), sort_item);

    int i = 0, value = 0;

    while (w > 0)
    {
        if (items[i].weight >= w)
        {
            items[i].weight = w;
            value += items[i].unit_cost * w;
            w = 0;
        }
        else
        {
            w -= items[i].weight;
            value += items[i].cost;
        }
        i++;
    }

    cout << "cost of stolen items: " << value << endl;

    return 0;
}