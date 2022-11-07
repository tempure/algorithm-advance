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

int cnt[10];

string get_min(int x) { //当前位的字符从大到小枚举，然后后面位置的一律字典序最小贪心
    //这样贪心才能确定当前位置可以放的最大的元素
    string res = to_string(x);
    cnt[x] -- ;

    for (int i = 0; i < 10; i ++ )
        for (int j = 0; j < cnt[i]; j ++ )
            res += to_string(i);

    cnt[x] ++ ;
    return res;
}

void solve() {
    string a, b;
    cin >> a >> b;
    if (sz(a) < sz(b)) {
        sort(all(a), greater<char>());
        cout << a << endl;
    }
    else {
        for (auto c : a) cnt[c - '0'] ++ ;
        string res;
        for (int i = 0; i < a.size(); i ++ ) //枚举每一位 从高到低
            for (int j = 9; j >= 0; j -- )
                if (cnt[j] && res + get_min(j) <= b) {
                    res += to_string(j);
                    cnt[j] -- ;
                    break;
                }
        cout << res << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}