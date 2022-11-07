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
//snippet-head

//最小点覆盖 裸匈牙利算法
//有个坑就是初始模式都是0 那对于0模式可以匹配掉的点 直接忽略


const int N = 110;

int n, m, k;
bool g[N][N], st[N]; //可以邻接矩阵 也可以邻接表
int match[N];


bool  dfs(int x) {
    for (int i = 1; i < m; i++) //main函数的循环时左边的点1~n-1 (0已经初始时候弄过了)
        //那么dfs里面就是处理右边待匹配的点
        if (!st[i] && g[x][i]) {  //注意是单向边的存储方式 注意方向
            st[i] = true;
            int t = match[i];
            if (t == 0 || dfs(t)) {
                match[i] = x;
                return true;
            }
        }

    return false;
}

int main() {
    while (cin >> n, n) {
        cin >> m >> k;
        memset(g, 0, sizeof g);
        memset(match, 0, sizeof match);

        while (k --) {
            int a, b, t;
            cin >> t >> a >> b;
            if (!a || !b) continue; //初始模式就是0
            g[a][b] = true;
        }
        //对匈牙利算法的理解：
        //每个点不会对其后边的点产生影响，因为假设一个没有匹配过妹子的男生匹配的女生恰好没有被匹配过
        //那就直接匹配上了，如果这个妹子被前面的男生匹配过了，那么只会让前面的男生重新匹配，而且由于算法的正确性 肯定会匹配成功
        //那么无论如何 这个男生后边的男生 就丝毫不会收到影响 所以下面的res才会遍历一次 然后加加

        int res = 0;
        for (int i = 1; i < n; i++) {
            memset(st, 0, sizeof st);
            if (dfs(i)) res ++;
        }

        cout << res << endl;
    }
}