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

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    auto isGood = [&](int l, int r) {
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                for (int k = j + 1; k <= r; k++) {
                    if (a[i] >= a[j] && a[j] >= a[k]) {
                        return false;
                    }
                    if (a[i] <= a[j] && a[j] <= a[k]) {
                        return false;
                    }
                }
            }
        }
        return true;
    };

    int ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (!isGood(j, i)) {
            j++;
        }
        ans += i - j + 1;
    }

    std::cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}