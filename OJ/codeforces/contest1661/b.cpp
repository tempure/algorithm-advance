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


//这种题套路比较固定，一般都是反向BFS
//https://zhuanlan.zhihu.com/p/495902994

int dis[40000];

void init() {
    for (int i = 1; i < 40000; i++) dis[i] = 999999;
    dis[0] = 0;
    queue<int> q;
    q.push(0);
    const int mod = 32768;
    while (!q.empty())
    {
        auto t = q.front(); q.pop();
        set<int> nxt;
        nxt.insert((t - 1 + mod) % mod);
        if (t % 2 == 0) nxt.insert(t / 2);
        nxt.insert((t + 32768) / 2);

        for (auto it : nxt)
        {
            if (dis[it] > dis[t] + 1)
            {
                dis[it] = dis[t] + 1;
                q.push(it);
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    cout << dis[n] << " ";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    init();
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}