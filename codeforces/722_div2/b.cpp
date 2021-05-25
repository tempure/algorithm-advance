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

const int N = 1e5 + 10;
vector<int> a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while (t --) {
        a.clear(); b.clear();
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            if (x <= 0) a.push_back(x);
            else b.push_back(x);
        }

        sort(a.begin(), a.end()); sort(b.begin(), b.end());

        if (a.size() == 0) {
            cout << 1 << endl;
            continue;
        }

        if (b.size() == 0) {
            cout << a.size() << endl;
            continue;
        }


        // for (auto x : a) cout << x << ' ';
        // cout << endl;
        // for (auto x : b) cout << x << ' ';
        // cout << endl;

        int x = b[0];

        bool flag = true;

        for (int i = 1; i < a.size(); i++)
            if (a[i] - a[i - 1] < x) {
                flag = false;
                break;
            }

        if (flag) cout << sz(a) + 1 << endl;
        else cout << sz(a) << endl;
    }

    return 0;
}