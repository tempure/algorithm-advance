#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll N = 1e18;
ll n, m;
map<ll, ll> d, q;

/*
宽搜以前的写法这题1e18没法做
https://www.acwing.com/problem/content/submission/code_detail/10846174/
user editorial 的bfs：https://cp-wiki.vercel.app/en/tutorial/atcoder/ABC188/#problem-f-1-1x2
但是我好像没太理解。。。。。
*/

int main() {
    cin >> n >> m;

    // memset(d, 0x3f, sizeof d);
    d[n] = 0;
    ll hh = 0, tt = 0;
    q[0] = n;

    while (hh <= tt) {
        ll t = q[hh ++ ];
        ll items[] = {t - 1, t * 2, t + 1};
        for (auto x : items)
            if (x >= 1 && x < N && d[x] > d[t] + 1) {
                d[x] = d[t] + 1;
                q[ ++ tt] = x;
            }
    }
    cout << d[m] << endl;
    return 0;
}