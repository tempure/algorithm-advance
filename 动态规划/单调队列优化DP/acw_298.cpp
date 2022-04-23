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

//POJ1821
//https://www.acwing.com/video/1956/
//https://www.acwing.com/solution/content/6676/
//https://www.acwing.com/solution/content/2130/

struct rec { int L, P, S; } a[110];
int n, m;
int f[110][16010], q[16010];

bool operator <(rec a, rec b) {
    return a.S < b.S;
}

int calc(int i, int k) {
    return f[i - 1][k] - a[i].P * k;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &a[i].L, &a[i].P, &a[i].S);
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++) {
        // 初始化单调队列
        int l = 1, r = 0;
        // 把最初的候选集合插入队列
        for (int k = max(0, a[i].S - a[i].L); k <= a[i].S - 1; k++) {
            // 插入新决策，维护队尾单调性
            while (l <= r && calc(i, q[r]) <= calc(i, k)) r--;
            q[++r] = k;
        }
        for (int j = 1; j <= n; j++) {
            // 不粉刷时的转移
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            // 粉刷第k+1~j块木板时的转移
            if (j >= a[i].S) {
                // 排除队头不合法决策
                while (l <= r && q[l] < j - a[i].L) l++;
                // 队列非空时，取队头进行状态转移
                if (l <= r) f[i][j] = max(f[i][j], calc(i, q[l]) + a[i].P * j);
            }
        }
    }
    cout << f[m][n] << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}