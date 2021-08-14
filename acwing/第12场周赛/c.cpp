#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

typedef long long LL;

using namespace std;

struct vertex
{
    LL his, min;
};

vertex tree[200000 * 4 + 4];

inline LL min(const LL a, const LL b)
{
    if (a < b)
        return a;
    else
        return b;
}

LL up;
void update(int v, int l, int r, int kl, int kr)
{
    if (l == kl && r == kr)
    {
        tree[v].his += up;
        tree[v].min += up;
    }
    else
    {
        int mid = (l + r) / 2;
        if (kl > mid)
            update(v * 2 + 1, mid + 1, r, kl, kr);
        if (kr <= mid)
            update(v * 2, l, mid, kl, kr);
        if (kl <= mid && kr > mid)
        {
            update(v * 2, l, mid, kl, mid);
            update(v * 2 + 1, mid + 1, r, mid + 1, kr);
        }
        tree[v].min = min(tree[v * 2].min, tree[v * 2 + 1].min) + tree[v].his;
    }
}

LL get(int v, int l, int r, int kl, int kr)
{
    if (l == kl && r == kr)
    {
        return tree[v].min;
    }
    else
    {
        int mid = (l + r) / 2;
        if (kl > mid)
            return get(v * 2 + 1, mid + 1, r, kl, kr) + tree[v].his;
        if (kr <= mid)
            return get(v * 2, l, mid, kl, kr) + tree[v].his;
        if (kl <= mid && kr > mid)
            return min(get(v * 2, l, mid, kl, mid), get(v * 2 + 1, mid + 1, r, mid + 1, kr)) + tree[v].his;
    }
}

int n, m;

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        cin >> up;
        update(1, 0, n - 1, i, i);
    }
    scanf("%d", &m);
    char ch;
    int l, r;
    for (; m > 0; m--)
    {
        scanf("%d %d%c", &l, &r, &ch);
        if (ch == ' ')
        {
            cin >> up;
            if (l <= r)
                update(1, 0, n - 1, l, r);
            else
            {
                update(1, 0, n - 1, l, n - 1);
                update(1, 0, n - 1, 0, r);
            }
        }
        else
        {
            if (l <= r)
                cout << get(1, 0, n - 1, l, r) << endl;
            else
                cout << min(get(1, 0, n - 1, l, n - 1), get(1, 0, n - 1, 0, r)) << endl;
        }
    }
    return 0;
}