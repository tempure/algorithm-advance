#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define endl '\n'
#define watch(x) cerr << (#x) << " is " << (x) << endl
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

/*
做法比较多，最简单的就是当作无向图存，然后直接从r2 DFS 一次就行了
还有一种做法就是，仔细观察只有 r2 -> r1 路径上的边会反向，只需要修改一下这些边的父子关系即可
*/

const int N = 5e5 + 10, M = N * 2;
int h[N];
int e[M], ne[M], idx;
int p[N];
int n, r1, r2;

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa){
    p[u] = fa;
    for(int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        if(j!=fa) dfs(j, u);
    }
}

void solve() {
    cin >> n >> r1 >> r2;
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n; i++){
        if(i!=r1){
            int fa;
            cin >> fa;
            add(fa, i), add(i, fa);
        }
    } 
    dfs(r2, -1);
    for(int i = 1; i <= n; i++){
        if(i!=r2)
            cout << p[i] << ' ';
    }
    puts("");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}