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

// const int N = 1e5; // 数组开sqrt(N) 的数量级即可 看循环的次数
map<int, pii> mii;

void divide(int n, int flag) {
    for (int i = 2; i * i <= n; i++) { //这里写成i <= n /i 会T掉，草
        if (n % i == 0) {
            if (flag == 1)while (n % i == 0) n /= i, mii[i].first++;
            else {
                while (n % i == 0) n /= i, mii[i].second++;
            }
        }
    }
    if (n > 1) {
        if (flag == 1) mii[n].first++;
        else mii[n].second++;
    }
}

void solve() {
    mii.clear();
    int a, b, k;
    cin >> a >> b >> k;
    divide(a, 1); divide(b, 2);
    int res = 0;
    for (auto t : mii) {
        if (t.second.first != t.second.second) res ++;
    }

    // for (auto t : mii) cout << t.first << ' ' << t.second.first << ' ' << t.second.second << endl;
    int sum = 0;
    for (auto t : mii) {
        sum += t.second.first + t.second.second;
    }
    if (a == b) res = 0;
    else if (gcd(a, b) == a || gcd(a, b) == b) res = 1;
    else res = 2;

    if (k >= res && k <= sum && k == 1 && res == 1) puts("YES");
    else if (k >= res && k <= sum && k != 1) puts("YES");
    else puts("NO");
    // if (res >= k && res <= sum) cout << "YES" << endl;
    // else cout << "NO" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}