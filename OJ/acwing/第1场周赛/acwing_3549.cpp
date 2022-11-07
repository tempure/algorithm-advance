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


//出处：https://codeforces.com/contest/934/problem/C

//最长非递减子序列 需要构造最长的 1111122222111112222 然后翻转中间的22222211111即可得到
//将该序列分成4段，枚举每一位，考虑这一位可以更新的状态即可
//题解：https://www.acwing.com/solution/content/50601/ 注意最后的代码是错的 思路没问题

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    while (n --) {
        int x; cin >> x;
        if (x == 1) {
            s1 ++;
            s3 = max(s2 + 1, s3 + 1);
        } else {
            s2 = max(s1 + 1, s2 + 1);
            s4 = max(s3 + 1, s4 + 1);
        }
    }
    cout << max(s3, s4) << endl;

    return 0;
}