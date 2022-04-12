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

void solve() {
    // map<string, string> m;
    int n;
    cin >> n;
    // set<string> s1, s2;
    vector<string> s1(n), s2(n);
    map<string, int> m;
    for (int i = 0; i < n; i++) {
        string s, t;
        cin >> s >> t;
        s1[i] = s;
        s2[i] = t;
        if (s == t) { //名字和姓氏有可能相同 好坑
            m[s] ++;
        }
        else {
            m[s]++;
            m[t]++;
        }
    }
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (m[s1[i]] > 1 && m[s2[i]] > 1) {
            // flag = false;
            puts("No");
            return;
        }
    }
    puts("Yes");

    // for (auto t : m) {
    //     cout << t.first << ' ' << t.second << endl;
    // }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}