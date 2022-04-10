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

//https://www.acwing.com/video/3789/

void solve() {
    map<string, int> cnt;
    map<string, string> hash;

    int n, m;
    cin >> n;
    while (n --) {
        set<string> S; //ababab 这样的 "ab" 只能算出现一次
        string str;
        cin >> str;
        //枚举所有子串
        for (int i = 0; i < sz(str); i++) {
            string s;
            for (int j = i; j < sz(str); j++) {
                s += str[j];
                S.insert(s);
            }
        }
        for (auto& word : S) {
            cnt[word] ++ ;
            hash[word] = str;
        }
    }

    cin >> m;
    while (m -- ) {
        string str;
        cin >> str;
        cout << cnt[str] << ' ';
        if (hash.count(str)) cout << hash[str] << endl;
        else cout << '-' << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}