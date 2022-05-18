#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300010;
ll x, y, a, b, c, idx;

//https://blog.csdn.net/qq_45288870/article/details/105178735
//排序贪心水题

struct node
{
    ll x, c;
} e[N];
bool cmp(node a, node b)
{
    return a.x > b.x;
}
int main()
{
    cin >> x >> y >> a >> b >> c;
    for (int i = 1; i <= a; i++) cin >> e[idx].x, e[idx++].c = 1;
    for (int i = 1; i <= b; i++) cin >> e[idx].x, e[idx++].c = 2;
    for (int i = 1; i <= c; i++) cin >> e[idx].x, e[idx++].c = 3;
    sort(e, e + idx, cmp);
    int res1 = 0, res2 = 0, res3 = 0;
    ll sum = 0;
    for (int i = 0; i < idx; i++)
    {
        if (res1 < x && e[i].c == 1)
        {
            res1++;
            sum += e[i].x;
        }
        if (res2 < y && e[i].c == 2)
        {
            res2++;
            sum += e[i].x;
        }
        if (e[i].c == 3) sum += e[i].x, res3++;
        if (res1 + res2 + res3 == x + y) break;
    }
    cout << sum;
    return 0;
}