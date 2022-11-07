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

//如果2个点能互相 攻击到 那么就连一条边 那么最大独立集就是答案
//对于一般图 求最大独立集是NPC问题，但是这个图可以二染色，就是二分图，可以匈牙利多项式时间解出
//这里所说的二染色，是指每个点“日”字连接的点颜色是不一样的 而且横纵坐标之和奇偶性不同 

#define x first
#define y second

const int N = 110;
int n, m, k;
pii match[N][N];
bool g[N][N], st[N][N];

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool dfs(int x, int y){
    for(int i = 0; i < 8; i++){
        int a = x + dx[i], b = y + dy[i];
        if(a < 1 || a > n || b < 1 || b > m) continue;
        if(g[a][b] || st[a][b]) continue;
        st[a][b] = true;

        pii t = match[a][b];
        if(t.x == 0 || dfs(t.x, t.y)){
            match[a][b] = {x, y};
            return true;
        }
    }
    return false;
}

int main(){
    cin >> n >> m >> k;

    for(int i = 0; i < k; i++){
        int x, y;
        cin >> x >>y;
        g[x][y] = true; //不能放的格子
    }

    int res  = 0;
    for(int i= 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            if((i + j) & 1 || g[i][j]) continue; //只需要单向匹配即可 就是枚举男的匹配女的
            memset(st, 0, sizeof st);
            if(dfs(i, j)) res ++;
        }

    cout << n * m - res - k  << endl;

    return 0;
}