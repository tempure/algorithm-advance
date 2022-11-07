#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 10;
int a[N], b[N];
int w, h, n;
vector<int>x, y;

void solve() {
    cin >> h >> w >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        x.push_back(a[i]);
        y.push_back(b[i]);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());

    for (int i = 0; i < n; i++) {
        cout << 1 + lower_bound(x.begin(), x.end(), a[i]) - x.begin();
        cout << ' ';
        cout << 1 + lower_bound(y.begin(), y.end(), b[i]) - y.begin();
        cout << endl;
    }
}


int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}