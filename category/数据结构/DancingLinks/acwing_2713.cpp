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
重复覆盖问题模板
和精确覆盖区别在于每次删除一列的时候，不会删除该列有1的位置的所有的行,因为这些行可以被多次选择
由于删除比较少，剪枝较差，所以需要用迭代加深的思路来优化

本质思路是IDA*，启发函数是“遍历所有列，每次对于当前列，选择当前列所有 有1的行，直到所有列被覆盖
但是计数器(选择的行数)只增加1”
启发函数的值肯定是要<=真实值的，假设需要选5行才能真正覆盖所有的列，但是启发式函数可能只选了3行
假设当前的IDA*搜索最大层数(选择的行数)为depth,当前层数为dep_current,
那么对于不等式 h()+dep_current >depth 意味着当前最大depth的IDA*算法不能搜出答案，需要扩大depth
*/

const int N = 10010; //最多所有位置都是1

int n, m;
int l[N], r[N], u[N], d[N], col[N], row[N], s[N], idx;
int ans[N];
bool st[110];  //启发函数标记该列是否被选

void init() {
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        col[i] = u[i] = d[i] = i;
        s[i] = 0;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}

void add(int &hh, int&tt, int x, int y) { //上下左右都是头插
    row[idx] = x, col[idx] = y, s[y] ++;
    u[idx] = y, d[idx] =  d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++;
}

int h() { //启发函数 返回当前最少需要的行数(才可以找到答案)
    int cnt = 0; //选择的行数
    memset(st, 0, sizeof st);
    for (int i = r[0]; i; i = r[i]) { //遍历当前还没有被覆盖的列
        if (st[col[i]]) continue; //当前列被选过就直接跳过
        cnt ++;
        st[col[i]] = true;
        for (int j = d[i]; j != i; j = d[j])
            for (int k = r[j]; k != j; k = r[k])
                st[col[k]] = true;
    }
    return cnt;
}

void remove(int p) { //删除第p列，但不删除该列有1的行 也不删除表头
    for (int i = d[p]; i != p; i = d[i]) {
        r[l[i]] = r[i];
        l[r[i]] = l[i];
    }
}

void resume(int p) {
    for (int i = u[p]; i != p; i = u[i]) {
        r[l[i]] = i;
        l[r[i]] = i;
    }
}

bool dfs(int k, int depth) { //k当前搜索的层数 depth当前IDA*最大的搜索层数
    if (k + h() > depth) return false;
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[p] > s[i])
            p = i; //找出1最少的列
    for (int i = d[p]; i != p; i = d[i]) {
        ans[k] = row[i];
        remove(i); //注意此处的删除恢复位置和精确覆盖不一样
        for (int j = r[i]; j != i; j = r[j]) remove(j);
        if (dfs(k + 1, depth)) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(j);
        resume(i);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    init();
    for (int i = 1; i <= n; i++) {
        int hh = idx, tt = idx;
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if (x) add(hh, tt, i, j);
        }
    }

    int depth = 0; //当前IDA*搜索的最大层数
    while (!dfs(0, depth)) depth++; //没有搜到就增大depth
    cout << depth << endl;
    for (int i = 0; i < depth; i++) cout << ans[i] << ' ';
    return 0;
}
