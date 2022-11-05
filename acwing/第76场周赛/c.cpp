#pragma optimize("-O2")
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

//这题还是有思维难度的
//https://www.acwing.com/solution/content/147460/

void solve() {
    int n;
    cin >> n;
    vector<int> up, down;
    string s;
    cin >> s;
    int now = 1;
    up.pb(now);
    for(int i = 0; i < sz(s); i++){
        if(s[i] == '<') up.pb(++now);
        else if(s[i] == '=') up.pb(now);
        else {
            up.pb(1); // a < b > c, 此时c直接设为1，就是符合的最小值
            now = 1;
        }
    }
    now = 1;
    down.pb(now);
    for(int i = sz(s) - 1; i >= 0; i --){
        if(s[i] == '>') down.pb(++now);
        else if(s[i] == '=') down.pb(now);
        else{
            down.pb(1);  //  a < b > d > c 此时 a 直接设为 1
            now = 1;
        }
    }
    reverse(all(down));
    // x < y < a < b > d > c  所以此时 a 显然不能为 1, 需为正向扫描时比 y 大的值，所以取 max
    for(int i = 0; i < n; i++){
        cout << max(up[i], down[i]) << ' ';
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}