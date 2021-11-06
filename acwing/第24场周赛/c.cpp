#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head


//开3个小根堆
//由于 std::priority_queue 不支持删除任意节点
//所以用懒标记，st[]标记已经被删除的点，pop() 的时候判断一下即可

const int N = 2e5 + 10;
int p[N];
priority_queue<pii, vector<pii>, greater<pii> > h[3];
bool st[N];

void solve() {
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        h[a - 1].push({p[i], i}); //转换为标号 0 1 2
    }

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        h[a - 1].push({p[i], i});
    }

    cin >> m;
    while (m --) {
        int c;
        cin >> c;
        while (h[c - 1].size() && st[h[c - 1].top().second]) h[c - 1].pop();
        if (h[c - 1].size() == 0) {
            cout << -1 << ' ';
            continue;
        }
        auto t = h[c - 1].top();
        cout << t.first << ' ';
        h[c - 1].pop();
        st[t.second] = true;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}