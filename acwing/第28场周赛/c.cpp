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

//就我不知道为啥刚开始一直挺费解的 突然就明白了 呃呃

//你所有能互相交换的都在一个连通块中，所以你最后能交换到达的位置肯定就在这个连通块里面
//a[i] 是一个 1~n 的排列
//写了很久C++都不知道的小细节：vector是可以直接进行比较的,一般直接排序然后进行比较

const int N = 110;
int n;
int a[N],  d[N], p[N];
vi A[N], B[N];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void merge(int a, int b) {
    if (a < 1 || a > n) return ;
    p[find(a)] = find(b);
}

void solve() {
    // vector<int> a = {1, 2, 3, 4};
    // vector<int> b = {1, 2, 3};
    // cout << (a == b) << endl;

    cin >> n;
    for (int i = 1; i <= n; i ++ ) p[i] = i;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    for (int i = 1; i <= n; i ++ ) cin >> d[i];

    for (int i = 1; i <= n; i ++ ) {
        merge(i - d[i], i);
        merge(i + d[i], i);
    }

    for (int i = 1; i <= n; i ++ ) {
        A[find(i)].push_back(i);
        B[find(i)].push_back(a[i]);
    }

    for (int i = 1; i <= n; i ++ ) {
        sort(B[i].begin(), B[i].end());
        if (A[i] != B[i]) {
            puts("NO");
            return;
        }
    }

    puts("YES");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}