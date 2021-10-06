#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int tr[N], a[N];
int ans[N];
int n;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] += c;
}

void init() {
    for (int i = 1; i <= n; ++i) {
        tr[i] += 1;
        int j = i + lowbit(i);
        if (j <= n) tr[j] += tr[i];
    }
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += tr[i];
    }
    return res;
}

//add(a[i],1)
//O(N) build tree but slower than O(N*logN) build ?
void solve() {
    cin >> n;
    for (int i = 2; i <= n; i++) cin >> a[i];
    // for (int i = 1; i <= n; i++) add(i, 1);
    init();

    for (int i = n; i >= 1; i--) {
        int k = a[i] + 1;
        int l = 1, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (sum(mid) >= k) r = mid;
            else l = mid + 1;
        }
        ans[i] = r;
        add(r, -1);
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
}

int main() {
    solve();
    return 0;
}