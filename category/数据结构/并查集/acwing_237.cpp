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


//离散化+DSU
//最多只有2e6个点 但是点下标最大1e9 所以要离散化
//保序离散化是排序+判重+二分 不需要保序的直接map/哈希表
//此题的离散化不需要保序 直接map即可

const int N = 2000010;
int n, m;
int p[N];
unordered_map<int, int> S;

struct Query {
    int x, y, e;
} query[N]; //存放离散化之后的询问的下标

int get(int x) {
    if (S.count(x) == 0) S[x] = ++n;
    return S[x];
}

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

int main() {
    int t;
    scanf("%d", &t);

    while (t --) {
        n = 0;
        S.clear();

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            int x, y, e;
            scanf("%d%d%d", &x, &y, &e);
            query[i] = {get(x), get(y), e}; //加入的时候离散化
        }

        //n就是离散化之后所有的点的个数
        for (int i = 1; i <= n; i++) p[i] = i; //初始化DSU

        //合并所有相等的约束条件
        for (int i = 0; i < m; i++) {
            if (query[i].e == 1) {
                int pa = find(query[i].x), pb = find(query[i].y);
                p[pa] = pb;
            }
        }

        //检查所有不等条件
        bool has_conflict = false;

        for (int i = 0; i < m; i++)
            if (query[i].e == 0) {
                int pa = find(query[i].x), pb = find(query[i].y);
                if (pa == pb) {
                    has_conflict = true;
                    break;
                }
            }
        if (has_conflict) puts("NO");
        else puts("YES");
    }
    return 0;
}

