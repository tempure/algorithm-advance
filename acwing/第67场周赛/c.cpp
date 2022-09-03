#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'
typedef vector<int> vi;
typedef long long LL;
typedef unsigned long long ull;
typedef pair<int, int> pii;
//head

// a[i] ... a[j]
// a[i] * 10^t  + a[j] = 0 (mod k) => a[i] * 10^t = -a[j] (mod k)
// 对于每个 a[j], 快速查询前面有多少个 a[i] 符合条件即可。
// 哈希表维护10的次幂以及和10次幂乘积对k的余数
// 然后数组反转一下，同样求 a[j] 拼接在 a[i] 前面（反过来）的数量
// 此题卡常，需要手写哈希

const int N = 200010, M = 10000007;

int n, m;
int a[N];
LL h[M];
int cnt[M];

//这里由于要存2个值 r, t, 就把r向前移2位，把t放在末尾。哈希的写法稍有不同。
int find(int r, int t) { //开放寻址 哈希
    LL key = r * 100ll + t;
    int k = key % M;
    while (h[k] != -1 && h[k] != key)
        if ( ++ k == M)
            k = 0;
    if (h[k] == -1) h[k] = key, cnt[k] = 0;
    return k;
}


LL work() {
    LL res = 0;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; i ++ ) {
        int r = a[i] % m;
        if (r) r = m - r;
        int t = 0, x = a[i];
        while (x) t ++, x /= 10;
        res += cnt[find(r, t)]; //前面有多少个 w, w*10^t + a[i] mod k = 0 (k为变量m)

        for (int j = 1, x = 10; j <= 10; j ++, x = x * 10ll % m)
            cnt[find((LL)a[i] * x % m, j)] ++ ;
    }
    return res;
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);

    LL res = work();
    reverse(a, a + n);
    res += work();

    printf("%lld\n", res);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}