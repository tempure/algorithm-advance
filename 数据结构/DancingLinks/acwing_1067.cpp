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

const int N = 5510; //所有1的数量加上第0行的head表头 注意这个模板没有列的表头

int n, m;
//l每个点的左边的节点 r右边的节点 d下边的 u上边的 s该列有多少个1 row点的行坐标 col列坐标
int l[N], r[N], u[N], d[N], s[N], row[N], col[N], idx;
int ans[N], top;

void init() { //初始化表头 表头一共以m + 1个点，最左边一个是哨兵 比列数多一列
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        u[i] = d[i] = i;
    }
    l[0] = m, r[m] = 0; //循环链表
    idx = m + 1; //点的内存分配指针
}

void add(int &hh, int &tt, int x, int y) { //在坐标(x,y)插入一个点
    row[idx] = x, col[idx] = y, s[y]++;
    //每次都是插到第0行表头的下边一行 是头插
    //hh tt每一行最左边2个指针，插入到这2个指针中间
    u[idx] = y, d[idx] =  d[y], u[d[y]] = idx, d[y] = idx;
    r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
    tt = idx ++; //tt向左移动到新加入的点的位置
}

void remove(int p) { //删除第p列 以及该列有1的所有的行
    r[l[p]] = r[p], l[r[p]] = l[p];  //删除列只需要删除表头即可
    //下边的这个二重循环，并没有删除第p列的元素，只删除了表头
    for (int i = d[p]; i != p; i = d[i])
        for (int j = r[i]; j != i; j = r[j]) {
            //删除一行 修改该行的每个元素的上下指针即可
            s[col[j]] --;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
}

void resume(int p) { //恢复一次remove的所有删除
    for (int i = u[p]; i != p; i = u[i])
        for (int j = l[i]; j != i; j = l[j]) {
            u[d[j]] = j, d[u[j]] = j;
            s[col[j]] ++;
        }
    r[l[p]] = p, l[r[p]] = p;
}

bool dfs() {
    if (!r[0]) return true; //第0行链表头右边已经被删完了 说明所有的列都已经被覆盖
    int p = r[0];
    for (int i = r[0]; i; i = r[i]) //找出1最少的一列 注意不要混淆r[]和row[]
        if (s[i] < s[p])
            p = i;
    remove(p); //先删去这个表头 表示这一列已经被覆盖 因为搜的时候只会找表头

    for (int i = d[p]; i != p; i = d[i]) { //遍历当前1最少的列的每一个1所在的行，每一行都横向遍历删除列
        ans[++top] = row[i]; //记录答案
        //删除该行除了当前被覆盖的列以外，其余所有1所在的列以及该列有1的所有行
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if (dfs()) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top --;
    }

    resume(p); //恢复现场 恢复表头
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    init();
    for (int i = 1; i <= n;  i++) { //读取所有点
        int hh = idx, tt = idx; //头插指针
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if (x) add(hh, tt, i, j); //是1就插入
        }
    }

    if (dfs()) {
        for (int i = 1; i <= top; i++) cout << ans[i] << ' ';
        cout << endl;
    }
    else cout << "No Solution!" << endl;

    return 0;
}
