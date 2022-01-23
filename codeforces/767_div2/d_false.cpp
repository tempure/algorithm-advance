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
    int n;
    cin >> n;
    set<string> S;
    map<string, int> mp;
    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        S.insert(t);
        if (!mp[t]) mp[t] = i;
    }
    for (string t : S) {
        if (sz(t) == 1) {
            puts("YES");
            return;
        }
        else if (sz(t) == 2) {
            if (t[0] == t[1]) {
                puts("YES");
                return;
            }
            string s = t;
            reverse(all(s));
            if (S.count(s)) {
                puts("YES");
                return;
            }
        }
        else if (sz(t) == 3) {
            if (t[0] == t[2]) {
                puts("YES");
                return;
            }
            //cba abc
            string tt = t;  //3 + 3
            reverse(all(tt));
            if (S.count(tt)) {
                puts("YES");
                return;
            }

            string temp = {t[1], t[0]}; //3  +2 bca cb
            if (S.count(temp) && mp[t] < mp[temp]) {
                puts("YES");
                return;
            }

            string temp2 = {t[2], t[1]}; //2 + 3 bc acb
            if (S.count(temp2) && mp[t] > mp[temp]) {
                puts("YES");
                return;
            }
        }
    }
    puts("NO");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}