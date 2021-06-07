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

const int N = 110;
int a[N];
int n;


int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int t; cin >> t;
    while (t --) {
        bool flag = true;
        int mm = 0xcfcfcfcf;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] < 0) {
                flag = false;
            }
            mm = max(mm, a[i]);
        }

        if (flag) {
            puts("YES");
            cout << mm + 1 << endl;
            for (int i = 0; i <= mm; i++) cout << i << ' ';
            cout << endl;
        } else {
            puts("NO");
        }
    }

    return 0; 
}
