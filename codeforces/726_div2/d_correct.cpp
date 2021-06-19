#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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

/*
分类讨论：
n是奇数：必败 因为要么是素数，要么必须给对手一个非2次幂的偶数，对手可以继续变成奇数，往复最后丢给自己素数
n是偶数但不是2的次幂：必胜 分析同上
n是2的次幂： 次数为奇数 必败 偶数必胜, 显然减去一个因子，要么继续是2的次幂，要么是偶数但不是2次幂
后者显然给对手必胜，所以只能继续减为2次幂丢给对手，所以根据次数奇偶即可
*/


void solve() {
    int n; cin >> n;
    if (n % 2 == 1) {
        cout << "Bob" << endl; //奇数 必败态
        return ;
    }

    int cnt = 0;
    while (n % 2 == 0) {
        cnt ++;
        n /= 2;
    }
    if (n > 1) { //非2的次幂
        cout << "Alice\n";
    } else if (cnt % 2 == 0) { //2的次幂，次数为偶数 必胜
        cout << "Alice\n";
    } else cout << "Bob\n"; //2的次幂，次数为奇数，必败
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}