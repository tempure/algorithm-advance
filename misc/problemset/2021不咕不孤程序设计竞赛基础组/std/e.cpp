#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Person
{
    int t, p;
};
bool operator<(const Person &lhs, const Person &rhs) { return lhs.t < rhs.t; }
Person peo[200010];
int num[200010], last[200010];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> peo[i].t >> peo[i].p;
    sort(peo + 1, peo + n + 1);
    for (int i = 1; i <= n; i++)
    {
        int p = peo[i].p;
        num[p]++;
        int d = peo[i].t - last[p];
        num[p] = max(num[p] - d, 0);
        last[p] = peo[i].t;
    }
    for (int i = 1; i <= m; i++)
    {
        int d = peo[n].t - last[i];
        num[i] = max(num[i] - d, 0);
    }
    int tmax = 0;
    for (int i = 1; i <= m; i++)
        tmax = max(tmax, num[i]);
    cout << peo[n].t + tmax;
    return 0;
}
