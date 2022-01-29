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

//二分+前綴和
//向量運算 曼哈頓距離
//當前二分枚舉的操作長度len要滿足 len <= 除了當前段外兩段合向量與終點的曼哈頓距離
//同時滿足len和這個曼哈頓距離奇偶性相同，因爲一上一下，一左一右可以抵消

const int N = 2e5 + 10;
int n, X, Y;
int sx[N], sy[N];
char str[N];

bool chk(int len) {
    for (int i = 1; i + len - 1 <= n; i ++ ) {
        int j = i + len - 1;
        int x = sx[n] - (sx[j] - sx[i - 1]); //前綴和，減去中間當前段，前後兩端的合向量
        int y = sy[n] - (sy[j] - sy[i - 1]);
        int d = abs(x - X) + abs(y - Y);
        if (d <= len && (d - len) % 2 == 0)
            return true;
    }
    return false;
}

void solve() {
    cin >> n;
    cin >> str + 1;
    cin >> X >> Y;
    for (int i =  1; i <= n; i++) {
        sx[i] = sx[i - 1], sy[i] = sy[i - 1];
        char c = str[i];
        if (c == 'U') sy[i] ++ ;
        else if (c == 'D') sy[i] -- ;
        else if (c == 'L') sx[i] -- ;
        else sx[i] ++ ;
    }
    if (abs(X) + abs(Y) > n || (X + Y - n) % 2) puts("-1"); //走不到終點
    else {
        int l = 0, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (chk(mid)) r = mid;
            else l = mid + 1;
        }
        cout << r << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}