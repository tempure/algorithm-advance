#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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
//head


string get(string s, int k) {
    while ((int)s.size() < k) {
        s = s + s;
    }
    while ((int)s.size() > k)
        s.pop_back();
    return s;
}

int main() {
    int n, k;
    string s;
    cin >> n >> k;
    cin >> s;

    string pref = "";
    pref += s[0];

    string mn = get(pref, k);

    for (int i = 1; i < n; i++) {
        if (s[i] > s[0])break;
        pref += s[i];
        mn = min(mn, get(pref, k));
    }
    cout << mn << "\n";
}