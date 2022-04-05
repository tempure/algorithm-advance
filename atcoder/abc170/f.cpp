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

//https://atcoder.jp/contests/abc170/submissions/14317157
//就很朴素的BFS, 每次枚举4个方向走的步数
//官方题解给的dijkstra什么鬼。。。。。。。。。。。。

#define rep(i,n) for(int i=0;i<(int)(n);i++)
vi dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
#define vii vector< vector<int> >
const ll inf = 1000000001;
#define in(x, a, b) (a <= x && x < b)

void solve() {
    int h, w, k;
    cin >> h >> w >> k;
    int sy, sx, ty, tx;
    cin >> sy >> sx >> ty >> tx;
    sy--; sx--; ty--; tx--;

    vector<string> s(h);
    rep (i, h) cin >> s[i];

    using P = pair<int, pii>;
    queue<P> qu;
    qu.push(P(0, pii(sy, sx)));

    vii dist(h, vi(w, inf));
    dist[sy][sx] = 0;
    while (qu.size() > 0) {
        P temp = qu.front();
        qu.pop();
        int cost = temp.first;
        int y = temp.second.first, x = temp.second.second;
        rep (di, 4) {
            for (int ha = 1; ha <= k; ha++) {
                int ny = y + dy[di] * ha, nx = x + dx[di] * ha;
                if (not in(ny, 0, h) or not in(nx, 0, w)) break;
                int ncost = cost + 1;
                if (s[ny][nx] == '@') break;
                if (dist[ny][nx] > ncost) {
                    dist[ny][nx] = ncost;
                    qu.push(P(ncost, pii(ny, nx)));
                }
                else if (dist[ny][nx] == ncost) continue;
                else break;
            }
        }
    }
    if (dist[ty][tx] == inf) {
        cout << -1 << endl;
    }
    else {
        cout << dist[ty][tx] << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}