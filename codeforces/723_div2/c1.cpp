#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
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

const int N = 2e5 + 10;
ll cha[N];
int a[N];
ll all[N], ans;
bool st[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        cha[i] = a[i] - cha[i - 1];
    }
    priority_queue<pii>q;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= 0) {
            ans++;
            st[i] = 1;
            continue;
            all[i] = all[i - 1] + a[i];
        }
        q.push({a[i], i});
        all[i] = all[i - 1];
    }
    while (!q.empty()) {
        auto t = q.top();
        q.pop();
        int num = t.first, pos = t.second;
        ll s = 0;
        st[pos] = 1;
        bool f = 1;
        for (int i = 1; i <= n; i++)
        {
            if (st[i])s += a[i];
            if (s < 0)
            {
                f = 0;
                break;
            }
        }
        if (f)ans++;
        else st[pos] = 0;
    }
}

int main() {
    int t;
    //cin>>t;
    t = 1;
    while (t--) {
        solve();
        cout << ans;
    }
    return 0;
}