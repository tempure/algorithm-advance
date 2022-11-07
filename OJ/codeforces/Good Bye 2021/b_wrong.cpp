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
    int n;
    cin >> n;
    cin >> s;
    if(s[0] == s[1]){
        cout << s[0] << s[1] << endl;
        return;
    }
    int pos = -1;
    int pos1 = -1;
    int len = sz(s);
    for (int i = 0 ; i < len - 1; i++) {
        if (s[i + 1] >= s[i]) {
            pos1 = i;
            break;
        }
    }
    if (pos1 == -1) {
        cout << s << endl;
        return;
    }
    int j = pos1;
    while (j + 1 < len && s[j + 1] <= s[j]) j++;
    if(s[j] < s[pos1]) pos = j;
    else pos = pos1;
    // if()
    // cout << j << endl;
    for (int i = 0; i <= pos; i++) cout << s[i];
    for (int i = pos; i >= 0; i--) cout << s[i];
    puts("");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}