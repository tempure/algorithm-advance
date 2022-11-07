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

//字典序最小 那么就枚举每个点的时候把点编号排序 从大到小搜
//因为先递归到最后 然后才压栈 最先搜的 就是在栈顶 如果用数组保存 那么逆序输出时候 就先输出最先搜的

const int N =  510, M = 2100;
int n = 500, m;
int g[N][N];
int ans[1100], cnt; //答案和边数是正比的 因为一个点可以多次在答案中 答案输出的是点的顺序
int d[N];


void dfs(int u){
    for(int i = 1; i <= n; i++)
        if(g[u][i]){
            g[u][i] --, g[i][u] -- ;
            dfs(i);
        }
    ans[++cnt] =  u;
}

int main(){
    cin >> m;
    while(m--){
        int a, b;
        cin >> a >> b;
        g[a][b] ++, g[b][a] ++;
        d[a] ++, d[b] ++;
    }

    int start = 1;
    //先找到一个度数不是0的点 因为题目的点的编号不是连续的 
    //然后再找到一个度数是奇数的点 如果不存在度数是奇数的点 那么就说明所有的点都是偶数度数 那么就随便一个不为零的开始即可
    while(!d[start]) start ++;
    for(int i = 1; i <= n; i++)
        if(d[i] & 1){
            start = i;
            break;
        }

    dfs(start);
    for(int i = cnt ;i ;i --) printf("%d\n", ans[i]);

    return 0;

}