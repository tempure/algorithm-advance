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

//题意有点绕：从0~50000中选出尽量少的数，使得每个区间[ai,bi]都至少ci个数被选, 求选出数的个数
//求最小值那么就是最长路问题了 题目保证有解 就不用判断正环了
//设s[i] 为1到i中被出的数的个数 也就是前i个数 dist[i] 同理 最后答案是dist[50001]
//需要满足: s[i] >= s[i - 1], s[i] - s[i - 1] <= 1, s[b] - s[a-1] >= c

const int N = 50010, M = 150010;

int n;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

void spfa(){
    memset(dist, 0xcf, sizeof dist);
    int hh = 0, tt = 1;
    q[0] = 0;
    dist[0] = 0;
    st[0] = true;

    while(hh != tt){
        int t = q[hh++];
        if(hh == N) hh = 0;
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(dist[j] < dist[t] + w[i]){
                dist[j] =  dist[t] + w[i];
                if(!st[j]){
                    q[tt ++] = j;
                    if(tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);

    for (int i = 1; i <= 50001; i++) {
        add(i - 1, i , 0);
        add(i, i - 1, -1);
    }

    while (n --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a ++; b++;
        add(a - 1, b, c);
    }

    spfa();
    printf("%d\n", dist[50001]);

    return 0;
}