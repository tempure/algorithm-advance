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

const int N =  1010;
int p1[N], p2[N];

int find1(int x) {
    if (x != p1[x]) p1[x] = find1(p1[x]);
    return p1[x];
}

int find2(int x) {
    if (x != p2[x]) p2[x] = find2(p2[x]);
    return p2[x];
}

void solve() {
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    for (int i = 0; i <= n; i++) p1[i] = i, p2[i] = i;

    while (m1 --) {
        int a, b;
        cin >> a >> b;
        p1[find1(a)] = find1(b);
    }
    while (m2 --) {
        int a, b;
        cin >> a >> b;
        p2[find2(a)] = find2(b);
    }
    int res = 0;
    vector<pii> ans;
    // exit(0);
    // cout << "*********" << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (find1(i) != find1(j) && find2(i) != find2(j)) {
                p1[find1(i)] = find1(j);
                p2[find2(i)] = find2(j);
                ans.push_back({i, j});
                res++;
            }
        }
    cout << res << endl;
    if (sz(ans)) for (auto t : ans) cout << t.first << ' ' << t.second << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}