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


//拓扑排序

const int N = 30010;

int n,m;
int h[N], e[N], ne[N], idx;
int d[N], seq[N];
bitset<N> f[N];

void add(int a, int b){
    e[idx] = b; ne[idx] = h[a], h[a] = idx++;
}

void topsort(){
    queue<int> q;
    for(int i = 1; i<=n; i++)
        if(!d[i]) q.push(i);
    int k = 0;
    while(q.size()){
        int t = q.front();
        q.pop();
        
        seq[k ++] = t; //储存排序后的序列
        for(int i = h[t]; ~i; i = ne[i]){
            int j = e[i];
            if(-- d[j] == 0) q.push(j);
        }
    }
}

int main(){
    cin >> n >> m;
    memset(h ,-1, sizeof h);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        d[b] ++;  // b点的入度加一
        add(a, b);
    }
    
    topsort();
    
    //从末尾开始DP的原因：
    //因为求的是每个点能向后走到的点的个数
    //那么在算某个点的时候 如果这个点的出边的点都已经算好了那么直接更新即可
    //这样一直递推到最开始就求解完毕了

    for(int i = n - 1; ~i; i--){ //从末尾开始 
        int j = seq[i];  //拓扑序列的点 开始往后走
        f[j][j]  = 1; //自己可到达自己
        for(int p = h[j]; ~p; p = ne[p])
            f[j] |= f[e[p]];  //e[p] 代表这条边指向的点  求并集
    }
    
    for(int i = 1; i <= n; i++) cout << f[i].count() << endl;
}