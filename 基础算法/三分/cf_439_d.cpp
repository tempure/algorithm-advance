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
mt19937 mrand(random_device{}());
int rnd(int x) { return mrand() % x;}
//head

//三分
//https://cp-algorithms.com/num_methods/ternary_search.html
//https://codeforces.com/blog/entry/12545
//https://codeforces.com/contest/439/submission/6814294

/*
考虑数组a和数组b的元素都放在数轴上，颜色不一样不过
然后从负无穷到正无穷移动k考虑需要的代价
显然函数是先减后增的单峰函数
*/

const int N = (int) 1e5 + 100;

int n, m;
LL a[N], b[N];

LL f(LL k) {
    LL ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < k) {
            ans += (k - a[i]);
        }
    }
    for (int i = 0; i < m; i++) {
        if (b[i] > k) {
            ans += (b[i] - k);
        }
    }
    return ans;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];
    LL ans = (LL) 1e18;
    int pos = 1;
    LL lo = 1, hi = (LL) 1e9;
    for (int it = 0; it < 100; it++) { //迭代100次
        assert(lo <= hi);
        LL mid1 = lo + (hi - lo) / 3;
        LL mid2 = hi - (hi - lo) / 3;
        assert(mid1 >= lo && mid1 <= hi);
        assert(mid2 >= lo && mid2 <= hi);
        if (f(mid1) < ans) {
            ans = f(mid1);
            pos = mid1;
        }
        if (f(mid2) < ans) {
            ans = f(mid2);
            pos = mid2;
        }
        if (f(mid1) >= f(mid2)) {
            lo = mid1;
        } else {
            hi = mid2;
        }
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}