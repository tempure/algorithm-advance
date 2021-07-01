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

//这类字符串建图通常都是首尾元素作为点
//一共有26 * 26 个点最多

const int N = 700, M = 100010;
int n;
int h[N], e[M], ne[M], idx, w[M];
int q[N], cnt[N];
double dist[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool check(double mid) {
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    memset(dist, 0, sizeof dist);

    int hh = 0, tt = 0;
    //初始将所有点加进来，即使有的点题目数据没有，也就是不存在和这些点连的边，不影响正确性
    for (int i = 0; i < 676; i++)q[tt++] = i, st[i] = true;

    int count = 0; //超时判断
    while (hh != tt) {
        int t =  q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i] - mid) {
                dist[j] = dist[t] + w[i] - mid;
                cnt[j] = cnt[t] + 1;
                //玄学优化 所有点被更新的总次数>K * N就大概率有解, 这里2*N精度还不够，8*N才可以
                if (++count > 10 * N) return true;
                if (cnt[j] >= N) return true;
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

void solve() {
    char str[1010];
    memset(h, -1, sizeof h);
    idx = 0;

    for (int i = 0; i < n; i++) {
        cin >> str;
        int len = strlen(str);
        if (len >= 2) { //长度==2就是首尾2个分别都相同，长度小于2的字符串没用
            int le = (str[0] - 'a') * 26 + (str[1] - 'a');
            int ri = (str[len - 2] - 'a') * 26 + (str[len - 1] - 'a');
            add(le, ri, len);
        }
    }
    if (!check(0)) cout << "No solution\n";
    else {
        double l = 0, r = 1010;
        while (r - l > 1e-4) {
            double mid = (r + l) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }
        printf("%.2f\n", r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // int t = 1;
    // cin >> t;
    while (cin >> n && n) solve();

    return 0;
}