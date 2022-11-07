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

//https://atcoder.jp/contests/abc215/editorial/2515

//枚举每个排序后的元素p，假设当前p的横坐标为xi, 当前二分值为mid，那么 xi -mid .....  xi...xi + 1......xn 当前状态
//就只在队列里面保留到xi-mid的横坐标，因为横坐标是排序后的，所以xi-mid之前的所有元素横坐标都满足，同时我们不断更新队头元素来更新最大和最小的纵坐标
//一边更新一边弹出队头，这样对于每个元素，都可以求出符合xi-mid的那些前面的元素中，是否纵坐标也能更新成功同时满足。

void solve() {
    int n;
    cin >> n;
    vector<pii> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
    sort(all(v));
    int l = 0, r = 1e9 + 1;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        queue<pii> que;
        bool flag = false; //当前的mid是否能被大于
        int MIN = 0x3f3f3f3f, MAX = 0; //满足横坐标前提下的纵坐标最值，也就是p前面所有的元素来维护的
        for (auto p : v) {
            while (!que.empty()) {
                if (que.front().x > p.x - mid) break; //队头已经不能再往后了，不然x就不满足了,也就是队头已经不能用来更新y了
                MIN = min(MIN, que.front().y);
                MAX = max(MAX, que.front().y);
                que.pop(); //如果队头元素的x坐标满足，那就一直弹出队头，同时更新y
            }
            if (MIN <= p.y - mid || MAX >= p.y + mid) flag = true;
            que.push(p); //当前元素入队尾
        }
        if (flag) l = mid;
        else r = mid - 1;
    }
    cout << r << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}