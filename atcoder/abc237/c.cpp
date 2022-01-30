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
    string s;
    string temp;
    cin >> s;
    int len = sz(s);
    int i = 0;
    int j = len - 1;
    int cnta = 0, cntb = 0;
    while (s[i] == 'a') i++, cnta++;
    while (s[j] == 'a') j--, cntb++;
    if (i >= j) {
        puts("Yes");
        return;
    }
    if(cnta > cntb){
        puts("No");
        return;
    }
    int cnt = 0;
    for (int k = i; k <= j; k++) temp.pb(s[k]);
    len = sz(temp);
    for (int i = 0; i < len; i++) {
        if (temp[i] != temp[len - i - 1]) {
            puts("No");
            return;
        }
    }
    puts("Yes");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}