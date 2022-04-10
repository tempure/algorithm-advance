#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 3e5 + 5, INF = 0x3f3f3f3f;
int n, a[maxn];

//https://zhuanlan.zhihu.com/p/495913136
//cf的题是越来越看不懂了。。。。。。。。。。。

LL solve(int maxv) {
    LL sum = 0;
    LL cnt1 = 0;
    for (int i = 1; i <= n; i++) {
        int d = maxv - a[i];
        sum += d;
        if (d & 1) cnt1++;
    }
    LL res;
    if (sum % 3 == 0) {
        res = max(cnt1 * 2LL - 1, sum / 3 * 2);
    }
    else if (sum % 3 == 1) {
        res = max(cnt1 * 2LL - 1, sum / 3 * 2 + 1);
    }
    else {
        res = max(cnt1 * 2LL - 1, sum / 3 * 2 + 2);
    }
    return res;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        int maxv = 0;
        for (int i = 1; i <= n; i++) cin >> a[i], maxv = max(maxv, a[i]);
        cout << min(solve(maxv), solve(maxv + 1)) << '\n';
    }
}