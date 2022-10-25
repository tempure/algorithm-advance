#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define endl '\n'
#define watch(x) cerr << (#x) << " is " << (x) << endl
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

//BIT维护一下，要求的就是当前数w[i]前面有多少个数比w[i] 大，后面有多少个比w[i]小
//注意题意所有数两两不同，所以假设离散化后w[i] = v, 那么整个数组里面比 w[i] 小的就是 v - 1个
//求后面比w[i]小的就是总共比w[i]小的，减去w[i]前面比w[i]小的


const int N = 1e6 + 10;
int n;
int w[N], xs[N], tr[N];

int lowbit(int x){
    return x & -x;
}

void update(int x, int v){
    for(int i =x; i<= n; i+=lowbit(i))
        tr[i] +=v;
}

int query(int x){
    int res = 0;
    for(int i = x; i; i -= lowbit(i))
        res += tr[i];
    return res;
}


void solve() {
    cin >> n;
    for(int i = 0; i< n; i++){
        cin >> w[i];
        xs[i] = w[i];
    }        
    sort(xs, xs + n);
    ll res = 0;
    for(int i = 0; i < n; i++){ //遍历每个元素
        int v = lower_bound(xs, xs + n, w[i]) - xs + 1; // + 1 BIT模板下标从1开始
        int q = query(v);
        res += 1ll * (i - q) * (v-1 - q);
        update(v,1);
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}