#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'
typedef vector<int> vi;
// typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
//head

//https://www.acwing.com/solution/content/113934/
//https://www.acwing.com/activity/content/code/content/3358679/

//二分图染色
//黑白可以对调 都是符合条件的 但是是不同的染色方法!

typedef long long LL;

const int N = 300010, M = N * 2, MOD = 998244353;

int n, m;
int h[N], e[M], ne[M], idx;
int col[N];
int s1, s2;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int pow2(int k)
{
    int res = 1;
    while (k -- ) res = res * 2 % MOD;
    return res;
}

bool dfs(int u, int c)
{
    col[u] = c;
    if (c == 1) s1 ++ ;
    else s2 ++ ;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (col[j] && col[j] != 3 - c) return false;
        if (!col[j] && !dfs(j, 3 - c)) return false;
    }
    return true;
}

void solve() {
    scanf("%d%d", &n, &m);
    memset(h, -1, (n + 1) * 4);
    memset(col, 0, (n + 1) * 4);
    idx = 0;

    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    int res = 1;
    for (int i = 1; i <= n; i ++ )
        if (!col[i])
        {
            s1 = s2 = 0;
            if (dfs(i, 1)) res = (LL)res * (pow2(s1) + pow2(s2)) % MOD;
            else
            {
                res = 0;
                break;
            }
        }

    printf("%d\n", res);
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}