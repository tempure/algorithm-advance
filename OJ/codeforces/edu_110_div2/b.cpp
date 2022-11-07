#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
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

const int N = 2010;
int a[N];
int tmp[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    vi v;
    while (t --) {
        int n; cin >> n;
        for (int i =  0; i < n; i++) cin >> a[i];
        int k = 0; //even
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 0) tmp[k++] = a[i]; //even
        }
        cnt = k;
        for (int i =  0; i < n; i++) {
            if (a[i] & 1) tmp[k++] = a[i];
        }

        if (cnt < n)sort(tmp + cnt + 1, tmp + n, greater<int>());

        // for (int i = 0; i < n; i++) cout << tmp[i] << ' ';
        // cout << endl;
        int res = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (__gcd(tmp[i], 2 * tmp[j]) > 1) res++;

        cout << res << endl;
    }

    return 0;
}