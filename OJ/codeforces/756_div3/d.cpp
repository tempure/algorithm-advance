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

//https://www.bilibili.com/video/BV1Ji4y1o7Pz?t=1401.1


//定义在p中排名为i的点到root的距离为 i-1
//也就是第1近离root的就是root本身

//然后每个点到其父亲节点，也是边权就是 i-1 - (rank[father[i]] - 1) = i - rank[father]

const int N = 2e5 + 10;
int a[N];
int p[N];
int r[N];
int f[N]; //边权数组
int root, n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == i) root = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        r[p[i]] = i;
    }
    bool flag = true;
    if (p[1] != root) flag = false;
    f[root] = 0;
    for (int i = 2 ; i <= n && flag; i++)
        if (r[a[p[i]]] > i)
            flag = false; //父亲节点排名比自己靠后，无解
        else f[p[i]] = i - r[a[p[i]]];
    if (!flag) cout << -1 << endl;
    else {
        for (int i = 1; i <= n; i++)
            cout << f[i] << ' ';
        cout << endl;
    }
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}