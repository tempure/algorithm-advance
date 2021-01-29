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
所有的边为行 所有的正方形为列
每个行对于所在的正方形就加点 意思就是破坏当前边会影响到的正方形
直接用vector的find()操作来找是否存在该边即可

问题就转换为：至少要选择破坏哪些边 才能破坏所有正方形
*/

const int N = 3600;

int n, m;
int l[N], r[N], u[N], d[N], col[N], row[N], s[N], idx;
vector<int> square[60]; //n*n这样的网格 有n^2+(n-1)^2 +....1个正方形
bool st[60];

void init() {
    for (int i = 0; i <= m; i++) {
        l[i] = i - 1, r[i] = i + 1;
        col[i] = u[i] = d[i] = i;
        s[i] = 0;
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

int h() {
    int res = 0;
    memset(st, 0, sizeof st);
    for (int i = r[0]; i; i = r[i]) {
        if (st[i]) continue;
        st[i] = true;
        res ++;
        for (int j = d[i]; j != i; j = d[j])
            for (int k = r[j]; k != j; k = r[k])
                st[col[k]] = true;
    }
    return res;
}

void remove(int p) {
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

bool dfs(int k, int depth) {
    if (k + h() > depth) return false;
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[p] > s[i])
            p = i;

    for (int i = d[p]; i != p; i = d[i]) {
        remove(i);
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

    int T; cin >> T;
    while (T --) {
        cin >> n;
        memset(st, 0, sizeof st); //此处先用st标记那些边是开始就没有的 后边启发函数复用这个数组
        int cnt;
        cin >> cnt;
        while (cnt --) {
            int x;
            cin >> x;
            st[x] = true;
        }

        m = 0; //正方形的个数
        for (int len = 1; len <= n; len ++) //枚举边长
            for (int a = 1; a + len - 1 <= n; a ++) //横纵的偏移量a,b
                for (int b = 1; b + len - 1 <= n; b++) {
                    auto& sq = square[++m]; //每一个正方形的边的vector
                    sq.clear(); //多组样例
                    int d = n * 2 + 1;
                    for (int i = 0; i < len; i++) { //加入每个正方形的上下左右边到该正方形的vector中
                        sq.push_back((a - 1) * d + b + i); //加一条上方向的边，从左到右的顺序
                        sq.push_back((a - 1) * d + b + i + d * len);//下方向的边，从左到右加边，比上方向多len*d
                        sq.push_back((a - 1) * d + b + n + d * i); //左方向，从上到下加边，比上方向多n
                        sq.push_back((a - 1) * d + b + n + d * i + len);//右方向比左边多len，也是从上到下顺序加边
                    }

                    for (auto x : sq) //判断当前正方形是否有残缺的边，有的话就不算该正方形
                        if (st[x]) {
                            m --;
                            break;
                        }
                }
        init();
        for (int i = 1; i <= n * (n + 1) * 2; i++) //所有的边
            if (!st[i]) {
                int hh = idx, tt = idx;
                for (int j = 1; j <= m; j++) { //看哪些正方形含有这条边
                    auto &sq = square[j];
                    if (find(sq.begin(), sq.end(), i) != sq.end())
                        add(hh, tt, i, j);
                }
            }
        int depth = 0;
        while (!dfs(0, depth)) depth ++;
        cout << depth << endl;
    }

    return 0;
}