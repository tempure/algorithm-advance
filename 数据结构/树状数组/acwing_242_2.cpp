#include <iostream>
#include <cstring>
using namespace std;
using ll = long long;

//区间加d 单点求和，直接用差分数组建立树状数组即可

const int N = 1e5 + 10;

int a[N], tr[N];
int n, m;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

ll sum(int x) {
    ll res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];

    return res;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) add(i, a[i] - a[i - 1]);

    while (m --) {
        char c; int x;
        int l, r, d;
        cin >> c;
        if (c == 'Q') {
            cin >> x;
            cout << sum(x) << endl;
        }
        else {
            cin >> l >> r >> d;
            add(l, d); add(r + 1, -d);
        }
    }
    return 0;
}