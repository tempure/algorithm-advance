#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i = a; i< n; i++)
#define per(i,a,n) for(int i=n-1; i>=a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define x first
#define y second
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//最小值 求最长路
/*
用前缀和思想，num[i]表示第i个小时开始的人有多少个
用前缀和s[i]来建图，但是不需要实现s[i]，只需要加边就可以了

由于是循环的，所以前缀和要分成2段来求，每次用的都是长度为8的一段
1~7的要加上末尾的一段才能补成8个小时

s[i] - s[i-1] >= 0
s[i] - s[i-1] <= num[i];
i >= 8, s[i] - s[i-8] >= r[i];
i >= 1 && i <= 7, s[i] + s[24] - s[16 + i] >= r[i]
s[24] >= s[0] + k, s[0] >= s[24] - k //保证s[24]是当前枚举的定值k
列式子后发现s[24]不是定值，不能直接差分约束，所以直接枚举s[24]，只有1000个最多
取最小的s[24]有解的就是答案，如果有正环则无解
*/

const int N = 30, M = 100;  //一共三类 72条边最多
int h[N], e[M], ne[M], w[M], idx;
int r[N];
int num[N]; //num[i]是i时刻来的服务员
int q[N];
int dist[N];
bool st[N];
int cnt[N];
int n;

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

bool v[30];
int ct = 0;
void dfs(int u) { //必要时写个 dfs检测0能不能走到所有点 来决定是否初始所有点入队
    v[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j]) continue;
        ct++;
        dfs(j);
    }
}

void build(int c) { //建图
    memset(h, -1 , sizeof h);
    idx = 0;
    for (int i = 1; i <= 24; i++) {
        add(i - 1, i, 0);
        add(i, i - 1, -num[i]);
    }
    for (int i = 8; i <= 24; i++) add(i - 8, i, r[i]);
    for (int i = 1; i <= 7; i++) add(i + 16, i, -c + r[i]); //c是定值 此时枚举的就是c也就是s[24]
    add(0, 24, c); //和0连接 来确定是定值
    add(24, 0, -c);
}

bool spfa(int c) {
    build(c);
    // dfs(0);
    // cout << "*********" << ct << endl;
    memset(cnt, 0, sizeof cnt);
    memset(st, 0, sizeof st);
    memset(dist, 0xcf, sizeof dist);
    dist[0] = 0;

    int hh = 0, tt = 1;
    q[0] = 0;
    st[0] = true;

    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] <  dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= 25) return false;
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T --) {
        for (int i = 1; i <= 24; i++) cin >> r[i];
        cin >> n;
        memset(num, 0, sizeof num);

        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            num[t + 1] ++; //下标变换为从1~24 0为虚拟原点腾出来
        }

        bool success = false;
        for (int i = 0; i <= 1000; i ++) { //枚举s[24] 这个参数 如果成立说明有解
            if (spfa(i)) {
                cout << i << endl;
                success = true;
                break;
            }
        }
        if (!success) puts("No Solution");
    }

    return 0;
}