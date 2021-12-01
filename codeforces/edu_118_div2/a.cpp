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

void solve() {
    ll p1, x1, p2, x2;
    cin >> x1 >> p1 >> x2 >> p2;
    // if ((x2 / x1) % 10 == 0 || (x1 / x2) % 10 == 0) {
    //     if ((x2 / x1) / 10 == p1 - p2 || (x1 / x2) % 10 == p2 - p1) {
    //         cout << '=' << endl;
    //         return;
    //     }
    // }
    string sx1 = to_string(x1);
    // string sp1 = to_string(p1);
    string sx2 = to_string(x2);
    // string sp2 = to_string(p2);
    if (sz(sx1) + p1 > sz(sx2) + p2) {
        cout << '>' << endl;
    }
    else if (sz(sx1) + p1 == sz(sx2) + p2) {
        while (x1 % 10 == 0) {
            x1 /= 10;
        }
        while (x2 % 10 == 0) {
            x2 /= 10;
        }
        string temp1 =  to_string(x1);
        string temp2 = to_string(x2);
        if (temp1 > temp2) {
            cout << '>' << endl;
        }
        else if (temp1 == temp2) cout << '=' << endl;
        else cout << '<' << endl;
        // if (sz(sx1) < sz(sx2)) {
        //     while (sz(sx1) < sz(sx2)) {
        //         sx1 += '0';
        //     }
        //     if (stoll(sx1) > x2) cout << '>' << endl;
        //     else if (stoll(sx1) == x2) cout << '=' << endl;
        //     else cout << '>' << endl;
        // }
        // else if (sz(sx1) > sz(sx2)) {
        //     while (sz(sx1) > sz(sx2)) {
        //         sx2 += '0';
        //     }

        //     if (stoll(sx2) > x1) cout << '<' << endl;
        //     else if (stoll(sx2) == x1) cout << '=' << endl;
        //     else cout << '>' << endl;
        // }
        // else cout << '=' << endl;
    }
    else cout << '<' << endl;
// else if (p1 == p2) {
//     if (x1 > x2) {
//         cout << '>' << endl;
//     }
//     if (x1 < x2) cout << '<' << endl;
//     if (x1 == x2) cout << '=' << endl;
// }
// else cout << '<' << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}