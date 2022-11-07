#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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
int n, k;
char a[N], gz[26];
char mn = 'z', mx = 'a';
int m[26];

#define LL long long
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define x first
#define y second
#define N 131072
#define pi acos(-1)

void solve() {
    int n, k;
    scanf("%d %d", &n, &k);
    char c[100005];
    scanf("%s", c);
    map<char, int> m;
    for (int i = 0; i < n; i++) {
        m[c[i]];
    }
    int cnt = 0;
    vector<char> v;
    for (auto &it : m) {
        it.y = cnt++;
        v.pb(it.x);
    }
    int a[100005];
    for (int i = 0; i < n; i++) {
        a[i] = m[c[i]];
    }
    if (k > n) {
        for (int i = n; i < k; i++) {
            a[i] = 0;
        }
    }
    else {
        int Max = m.size();
        a[k - 1]++;
        for (int i = k - 1; i >= 0; i--) {
            if (a[i] >= Max) {
                a[i] = 0;
                a[i - 1]++;
            }
            else {
                break;
            }
        }
    }
    for (int i  = 0; i < k; i++)
        printf("%c", v[a[i]]);
    printf("\n");
}


int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}