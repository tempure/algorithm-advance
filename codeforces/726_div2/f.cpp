#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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

/*
分类讨论，二分图还是非二分图
二分图：考虑任何一条路径，如果路径2端点颜色不同，染色后用x表示黑，y表示白色，假设路径是x->y->x,一个重要的性质是给第一条边加v，第二条边减v
那么结果是y不变，一个x+v,另外一个x-v，当然，也可以给不同颜色的x,y同时加v，仅此两种操作进行考虑。

如果是二分图：点权都变为v[i]-t[i],那么先染色，考虑x点集合和y点集合，对于上述的两种操作可知相同颜色点总可以一加一减，不同的总可以同时加
但是无论哪种操作，都不会改变这两个集合的相对大小，有解的情况是最后所有点权都是0，意味着黑点和白点集合元素的和必须相等才有解

非二分图，总有解，找出一个不能二染色的边：假设是x->x，由于非二分图一定存在环，因为树可以一层黑一层白，所以无环图必然是二分图
那么可以找到一个两端点都是相同颜色的边，而且在一个环中，那么可以固定其中一个点，枚举其他所有点和该点组成的点对，把其他点变成0
由于是环，所以这两个颜色相同的点有2条路径可以走，一条是可以+v -v 的，直接走是同时+-v，结合二种操作可以将一个点+2v 或者-2v
这种情况下要所有点的和都是偶数，即所有x的点和y的点和是偶数

其实看官方题解：如果初始所有v和所有t奇偶性不同就无解，因为每次操作都是对v进行偶数加减操作，不会改变奇偶性
如果奇偶性不同，那么和也必然是奇数，无解，和上面的推理做法结论是一样的。
*/

const int N = 2e5 + 10;
vector<long long> adj[N];
long long s[N], n, m;
bool bipartite()
{
    bool bip = true;

    for (long long i = 0; i < n; i++)
        s[i] = -1;

    queue<long long> q;

    for (long long i = 0; i < n; i++) {
        if (s[i] != -1)continue;

        q.push(i);
        s[i] = 0;

        while (!q.empty()) {
            long long v = q.front();
            q.pop();

            for (long long u : adj[v]) {
                if (s[u] == -1) {
                    s[u] = s[v] ^ 1;
                    q.push(u);
                } else bip &= s[u] != s[v];
            }
        }
    }
    return bip;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    long long T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        for (long long i = 0; i < n; i++)
            adj[i].clear();

        vector<long long> v(n), t(n);
        long long p1 = 0, p2 = 0;
        for (long long i = 0; i < n; i++) {
            cin >> v[i];
            p1 = (p1 + abs(v[i])) % 2;
        }
        for (long long i = 0; i < n; i++) {
            cin >> t[i];
            p2 = (p2 + abs(t[i])) % 2;
        }

        for (long long i = 0; i < m; i++) {
            long long a, b;
            cin >> a >> b;
            --a, --b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        if (p1 != p2) {
            cout << "NO\n";
            continue;
        }

        if (bipartite() == false) {
            cout << "YES\n";
        } else {
            vector<long long> c(2, 0);

            for (int i = 0; i < n; i++) {
                c[s[i]] += v[i] - t[i];
            }

            if (c[0] == c[1]) {
                cout << "YES\n";
                // cout << c[0] << ' ' << c[1] << endl;
            } else cout << "NO\n";
        }
    }

}