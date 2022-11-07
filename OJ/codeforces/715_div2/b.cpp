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

const int N = 3e5  + 10;
char str[N];
int len;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while (t --) {
        cin >> len;
        cin >>  str;
        int st = 0, sm = 0;
        bool flag = true;
        for (int i = 0; str[i]; i++) {
            if (str[i] == 'T') st ++;
            else sm ++;
            if (sm > st) {
                flag = false;
                break;
            }
        }
        if (st != 2 * sm) flag = false;

        st = 0, sm = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (str[i] == 'T') st ++;
            else sm ++;
            if (sm > st) {
                flag = false;
                break;
            }
        }
        if (st != 2 * sm) flag = false;
        if (flag) puts("YES");
        else puts("NO");
    }
    return 0;
}