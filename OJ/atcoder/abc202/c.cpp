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



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<int> A(N), B(N), C(N);

    //注意题目元素都从1开始，但是数组下标为0，所以全部元素减去1
    for (auto &x : A) {
        cin >> x;
        x  -= 1;
    }

    for (auto &x : B) {
        cin >> x;
        x -= 1;
    }

    for (auto &x : C) {
        cin >> x;
        x -= 1;
    }

    vector<int> count(N);
    for (int j = 0; j < N; j++) count[B[C[j]]] ++;

    ll ans = 0;

    for (int i =  0; i < N; i++) ans += count[A[i]];

    cout << ans << endl;

    return 0;
}
