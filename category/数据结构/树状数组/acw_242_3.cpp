#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m;

int tr[N], a[N];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tr[i] += c;
    }
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += tr[i];
    return res;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) add(i, a[i] - a[i - 1]);

    for (int i = 0; i < m; i++) {
        char x;
        cin >> x;
        if (x == 'Q') {
            int d; cin >> d;
            cout << sum(d) << endl;
        }
        else if (x == 'C') {
            int l, r , d;
            cin >> l >> r >> d;
            add(l, d), add(r + 1, -d);
        }
    }
}

int main() {
    solve();
    return 0;
}