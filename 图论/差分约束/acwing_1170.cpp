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
ll mulmod(ll a, ll b) {ll res=0;a%=mod;assert(b>=0);for(;b;b>>=1){if(b&1)res=(res+a)%mod;a=2*a%mod;}return res;}
ll powmod(ll a, ll b) {ll res=1;a%=mod;assert(b>=0);for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//第一个就是判负环 全部加入队列跑一次SPFA即可
//所有奶牛的距离都是相对距离，所以需要虚拟原点，假设所有牛都在数轴的正半轴 所有点都在x0的左边 也就是说x0是最右边的
//对于第二个要求 直接把1号点固定在0 也就是 x1 = 0 因为都是相对距离 不影响距离 最后看一下xn是不是可以无限大 这也等价于1号点到其他点的最短距离
//但是虚拟原点 不需要实现 实际上 在判断负环的时候所有点都已经入队 可以起到同样的效果
//求一下xn的最长路 如果无穷大 就是无穷大 否则就是最大值

//约束条件：xi <= x[i+1] + 0, xb <= xa + l, xa <= xb - d 

const int INF = 0x3f3f3f3f;
const int N = 1010, M = 21010;  //边数判断就是满足条件的类 每类需要多少点 全部加起来
//因为加边 的时候 会满足所有条件 也就是说每个条件 都要单独加边

int q[N], h[N], e[M], ne[M], idx, w[M], cnt[N], dist[N];
bool st[N];
int n, m1, m2;

void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

bool spfa(int sz){
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    int hh = 0, tt = 1;
    for(int i = 1; i <= sz; i++){  //加入队列 求负环
        dist[i] = 0;
        q[tt++] = i;
        st[i] = true; 
    }

    while(hh != tt){
        int t = q[hh++];
        if(hh == N) hh = 0;
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(dist[j] > dist[t] + w[i]){
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j] >= n)  return false;
                if(!st[j]){
                    q[tt++] = j;
                    if(tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }

    return true;
}

int main(){
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n, &m1, &m2);
    for(int i = 1; i < n; i++) add(i + 1, i, 0);
    while(m1 --){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if(b < a ) swap(a, b);
        add(a, b, c);
    }
    while(m2 --){
        int a,b ,c;
        scanf("%d%d%d", &a, &b, &c);
        if(b < a) swap(a, b);
        add(b, a, -c);
    }

    if(!spfa(n)) puts("-1"); //前n个点的图有负环
    else{
        spfa(1); //将第一个点放进去求
        if(dist[n] == INF) puts("-2");
        else printf("%d\n", dist[n]);
    }
    return 0;    
}
