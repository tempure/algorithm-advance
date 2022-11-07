#include <bits/stdc++.h>
using namespace std;

//不太懂啊。。。题解和谜语人一样

/*
题解最后一句：However, if the number of ones is equal to the number of zeros, 
we can actually assign the i-th bit anything we like. 
The rough sketch of the proof is that if x is inside a then x⊕2^i is also inside a.
？？？
*/

const int N = 2e5 + 5;
int p[N], cnt[32][2];

void solve() {
    memset(cnt, 0, sizeof cnt);
    int l, r; cin >> l >> r;
    for (int i = l; i <= r; ++i) {
        int x; cin >> x;
        for (int j = 0; j <= 30; ++j, x >>= 1)
            cnt[j][x & 1]++;
    }
    int ans = 0;
    for (int i = 0; i <= 30; ++i) {
        ans |= ((cnt[i][0] < cnt[i][1]) * (1 << i));
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}