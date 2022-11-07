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


set<string> s;

int res = 0;

void solve(int t) {
    if(t!=1){
        string temp;
        cin>> temp;
    }
    string s1, s2;
    cin >> s1 >> s2;
    string a,b,c,d;
    a = s1[0], b = s1[1];
    c = s2[1], d = s2[0];
    if(sz(s) > 0 && (s.count(a + b + c + d) || s.count(b + c + d + a) ||
        s.count(c + d + a + b) || s.count(d + a + b + c))) {
        if(t!=1) return;
    }
    // cout << a << b << c << d << endl;

    res++;

    s.insert(a + b + c + d);
    s.insert(b + c + d + a);
    s.insert(c + d + a + b);
    s.insert(d + a + b + c);
}

int main() {
    int t = 1;
    cin >> t;
    for(int i = 1; i<= t; i++) solve(i);
    cout << sz(s) <<endl;
    return 0;
}