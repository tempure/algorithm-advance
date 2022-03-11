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

//https://www.bilibili.com/video/BV1U3411W7uj
//https://codeforces.com/contest/1651/submission/149163309
//先找出轮廓点，然后从轮廓点开始反向宽搜

void solve() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> x(n), y(n);
    std::set<std::pair<int, int>> s;
    std::map<std::pair<int, int>, int> id;
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
        id[ {x[i], y[i]}] = i;
    }

    for (int i = 0; i < n; i++) {
        s.emplace(x[i] - 1, y[i]);
        s.emplace(x[i] + 1, y[i]);
        s.emplace(x[i], y[i] - 1);
        s.emplace(x[i], y[i] + 1);
    }

    std::vector<std::pair<int, int>> ans(n, { -1, -1});

    std::queue<std::array<int, 4>> q;
    for (auto [x, y] : s) {
        if (!id.count({x, y})) {
            q.push({x, y, x, y});
        }
    }

    while (!q.empty()) {
        auto [x, y, fx, fy] = q.front();
        q.pop();

        for (auto [nx, ny] : {std::pair(x - 1, y), {x + 1, y}, {x, y - 1}, {x, y + 1}}) {
            if (!id.count({nx, ny})) {
                continue;
            }
            ans[id[ {nx, ny}]] = {fx, fy};
            id.erase({nx, ny});
            q.push({nx, ny, fx, fy});
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i].first << " " << ans[i].second << "\n";
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}