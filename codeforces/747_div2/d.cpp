#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

//seems code is a bit long
//use dfs 2 colour
//use fake node to make 2 points connected with fake node have the same color, we onluy need ONE fake node
//dfs every component, if a component is bipartite, ans plus `ans += max(c[0],c[1]);` see this line:
//it means imposter and crewmate is relative, for a bipartite graph,the 2 colour's nodes amount isn't same(consider 3 nodes in a line)
//so we need a bigger amount of this 2 colour's nodes

void solve() {

}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}