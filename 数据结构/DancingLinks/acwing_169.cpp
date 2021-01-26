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

/*
数独，精确覆盖问题
行代表所有格子可能填的情况，16*16*16 每个格子能填16种
列是所有的约束条件：
1.每个格子只能填一个数 一共16*16
2.每行都是0~15只填一个 一共16*16
3.列和条件2相同 一共16*16
4.每个宫也是只能0~15各填一个  一共16*16

所以有4096行 1024列 但是1的个数是稀疏的 计算最多的1的个数：
只考虑每一行中1可能出现的最多次数即可，每一行代表一个格子选择的字母，因为只是“一个格子,一个字母”，所以在4种列的约束条件中，每一种都最多只会出现一次。
举例子就是一个格子，不可能在“每个格子恰好填一个数”这一类中出现2次，也不可能在“每行0~15恰好出现一次”中出现2次，其余的约束条件同理。
所以一行中“最多”只会出现4次1，那么最多的1的点个数就是4096 * 4，加上表头的1024 + 1个点，大约是17000多个点，开18000即可，开到20000是有点浪费空间了。
*/

const int N = 18000; //每行最多4个点，4096+1024+1个1最多
int m = 16 * 16 * 4; //列数
int u[N], d[N], l[N], r[N], s[N], col[N], row[N], idx;
int ans[N], top;

struct Op {
    int x, y; //坐标
    char z; //该坐标填的字母
} op[N];

char g[20][20];

void init() {
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        s[i] = 0;
        d[i] = u[i] = i;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}

void add(int &hh, int &tt, int x, int y) {
    row[idx] = x, col[idx] = y, s[y] ++;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++;
}

void remove(int p) {
    r[l[p]] = r[p], l[r[p]] = l[p];
    for (int i = d[p]; i != p; i = d[i])
        for (int j = r[i]; j != i; j = r[j]) {
            s[col[j]] --;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
}

void resume(int p) {
    for (int i = u[p]; i != p; i = u[i])
        for (int j = l[i]; j != i; j = l[j]) {
            u[d[j]] = j, d[u[j]] = j;
            s[col[j]] ++;
        }
    r[l[p]] = p, l[r[p]] = p;
}

bool dfs() {
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[i] < s[p])
            p = i;
    remove(p);
    for (int i = d[p]; i != p; i = d[i])
    {
        ans[ ++ top] = row[i];
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if (dfs()) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top -- ;
    }
    resume(p);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> g[0]) {
        for (int i = 1; i < 16; i++) cin >> g[i];
        init();

        for (int i = 0, n = 1; i < 16; i++) //n是行号
            for (int j = 0; j < 16; j++) {
                int a = 0, b = 15;
                if (g[i][j] != '-') a = b = g[i][j] - 'A';//一个位置已经填好了那么就让a和b都是已经填的字母
                for (int k = a; k <= b; k++, n ++) { //枚举该位置填什么
                    int hh = idx, tt = idx;
                    op[n] = {i, j, k + 'A'};
                    add(hh, tt, n, i * 16 + j + 1); //加1是因为行列下标都从1开始
                    add(hh, tt, n, 256 + i * 16 + k + 1);
                    add(hh, tt, n, 256 * 2 + j * 16 + k + 1);
                    add(hh, tt, n, 256 * 3 + (i / 4 * 4 + j / 4) * 16 + k + 1); //每个宫，宫从0开始到15
                }
            }
        dfs();
        for (int i = 1; i <= top; i++) {
            auto t = op[ans[i]];
            g[t.x][t.y] = t.z;
        }
        for (int i = 0; i < 16; i++) puts(g[i]);
        puts("");
    }
    return 0;
}
