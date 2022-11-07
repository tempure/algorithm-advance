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

//模拟

void solve() {
    string s;
    cin >> s;
    set<char> hash;
    vector<char> cs;

    //枚举所有长度为26的区间
    for (int i = 25; i < sz(s); i++) {
        hash.clear();
        bool flag = true;
        for (int j = i - 25; j <= i; j++)
            if (s[j] != '?' && hash.count(s[j])) {
                flag = false;
                break;
            }
            else hash.insert(s[j]);
        if (flag) { //找到一个合法区间
            cs.clear();
            for (char c = 'A'; c <= 'Z'; c++)
                if (!hash.count(c)) cs.pb(c);
            for (int j = i - 25, k = 0; j <= i; j ++)
                if (s[j] == '?')
                    s[j] = cs[k++];
            for (auto &c : s) if (c == '?') c = 'A'; //剩下所有位置全部填A
            cout << s << endl;
            return;
        }
    }
    puts("-1");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}