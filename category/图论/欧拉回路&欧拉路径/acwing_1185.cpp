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

//26个字母作为点 然后单词作为边 求是否存在欧拉路径 注意这是有向图 因为字母是点
//除了起点终点 其余点都满足出度等于入度 而且所有边都连在一起(dfs/并查集) 判断连通即可
//边上的字母不重要 不用记录 只需要记录端点的2个字母即可

const int N = 30;

int n, m;
int p[N];
bool st[N];
int din[N], dout[N];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

int main() {
    char str[1010];

    int t;
    cin >> t;
    while (t --) {
        scanf("%d", &n);
        memset(din, 0, sizeof din);
        memset(dout, 0, sizeof dout);
        memset(st, 0, sizeof st);
        for (int i = 0; i < 26; i++) p[i] = i; //初始化并查集

        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            int len = strlen(str);
            int a = str[0] - 'a', b = str[len - 1] - 'a';
            st[a] = st[b] = true;
            dout[a] ++, din[b] ++;
            p[find(a)] = find(b);
        }

        int start = 0, end = 0;
        bool success = true;

        for (int i = 0; i < 26; i++)
            if (din[i] != dout[i]) {
                if (din[i] == dout[i] + 1) end ++;
                else if (din[i] + 1 == dout[i]) start++;
                else {
                    success = false;
                    break;
                }
            }
        //如果上边的if没有进入 说明所有点都是入度==出度
        if (success && !(!start && !end || start == 1 && end == 1)) success = false; //有多个起点和终点 那就不满足

        //判断连通性
        int rep = -1;
        for (int i = 0; i < 26; i++)
            if (st[i]) { //st[i]是已经有单词 也就是右边的前提下 而且没有在并查集中 说明是孤立边
                if (rep == -1) rep = find(i);
                else if (rep != find(i)) {
                    success = false;
                    break;
                }
            }

        if (success) puts("Ordering is possible.");
        else puts("The door cannot be opened.");
    }

    return 0;
}
