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

const int N = 1e6 + 20;
string a[N];

void solve() {
    int n, m;
    cin >> n >> m;
    int X, Y;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 'L') {
                X = i, Y = j;
            }
        }
    int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    queue<pair<int, int> > q;
    q.push({X, Y});
    while (q.size()) {
        auto t = q.front();
        q.pop();
        int x = t.first, y = t.second;
        if (a[x][y] == '#') continue;
        int cnt = 0;
        int tempx, tempy;
        for (int i = 0; i < 4 ; i++) {
            if (x + dx[i] >= 1 && x + dx[i] <= n &&
                    y + dy[i] >= 1 && y + dy[i] <= m &&
                    a[x + dx[i]][y + dy[i]] == '.') {
                cnt++;
                tempx = x + dx[i], tempy = x + dy[i];
                q.push({x + dx[i], y + dy[i]});
            }
        }
        if (a[x][y] == '.' && cnt <= 1) {
            a[x][y] = '+';
            // q.push({tempx, tempy});
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << a[i][j] << ' ' ;
        }
        cout << endl;
    }
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}