#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const ll mod = 1e9 + 7;

const int N = 1e5 + 10;
int a[N];
ll s[N];

void solve() {
    int cnt = 0;
    int n; cin >> n;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
        s[i] = s[i - 1]  + a[i];
    }
    for (int i = 1; i < n; i++) {
        if (s[i] == sum - s[i])
            cnt++;
    }
    cout << cnt << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}