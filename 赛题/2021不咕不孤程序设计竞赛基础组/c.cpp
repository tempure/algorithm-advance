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

int v[1010];

void solve() {
    int n;
    cin >> n;
    vector<string> s;
    string temp = "";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.pb(to_string(x));
        // temp += to_string(x);
    }

    string MIN = "999999999";
    int pos;
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            temp += s[j];
        }
        for (int k = 0; k < i; k++)
            temp += s[k];
        if (temp < MIN) {
            MIN = temp;
            pos = i;
        }
        temp = "";
    }
    for (int i = pos; i < n; i++) cout << s[i] << ' ';
    for (int i = 0; i < pos; i++) cout << s[i] << ' ';
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}