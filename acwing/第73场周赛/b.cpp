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

set<string> S;

void shift(string s[]){ //交换实现顺时针旋转 90 度
    swap(s[0][0], s[0][1]);
    swap(s[0][0], s[1][0]);
    swap(s[1][0], s[1][1]);
}

void solve() {
    int n;
    cin >> n;
    string s[2], t;
    for(int i = 0; i < n; i++){
        cin >> s[0] >> s[1];
        t = s[0] + s[1];
        for(int j = 0; j< 3; j++){
            shift(s);
            t = min(t, s[0] + s[1]); //字典序最小的放入就行了
        }
        S.insert(t);
        if(i !=  n-1) cin >>  t; //吞掉 **
    } 
    cout << sz(S) << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}