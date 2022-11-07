#include <bits/stdc++.h>

using namespace std;

#define N 200100
#define MOD 998244353
#define ll long long
#define rep(i, n) for(int i = 0; i < n; ++i)

//https://atcoder.jp/contests/abc226/editorial/2890

//直接反向递推就可以了，不用什么拓扑排序最短路之类的技巧

ll t[N];
int k[N];
vector<int>e[N];

bool used[N];

int main(void) {
    int n, x;
    ll ans = 0;
    rep(i, N)used[i] = false;

    cin >> n;
    rep(i, n) {
        cin >> t[i];
        cin >> k[i];
        rep(j, k[i]) {
            cin >> x;
            e[i].push_back(x - 1);
        }
    }

    used[n - 1] = true;
    for (int i = n - 1; i >= 0; i--) {
        if (used[i]) {
            ans += t[i];
            rep(j, k[i]) {
                used[e[i][j]] = true;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
