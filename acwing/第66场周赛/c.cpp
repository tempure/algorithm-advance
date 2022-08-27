#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
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

//先把出现次数为一的对半分，如果恰好对半，结束
//否则就一个集合比另外一个集合多一个超级数
//如果一个元素出现的次数 > 2, 就可以分一个加到少一个元素的集合里面，其余所有元素放在另外一个集合即可

const int N = 110;
vi p[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        p[x].pb(i); //每个元素出现的下标
    }
    int cnt = 0;
    for (int i = 0; i < N; i++)
        if (p[i].size() == 1) cnt++;
    string res(n, 'A');
    //先把出现一次的对半分
    for (int i = 0, k = 0; i < N; i ++ )
        if (p[i].size() == 1) {
            k ++ ;
            if (k <= cnt / 2) res[p[i][0]] = 'A'; //A是较少的一半，ceil(cnt/2)
            else res[p[i][0]] = 'B';
        }
    bool flag = true;
    if (cnt & 1) {
        flag = false;
        for (int i = 0; i < N; i++)
            if (p[i].size() > 2) {
                flag = true;
                res[p[i][0]] = 'A';
                for (int j = 1; j < p[i].size(); j++)
                    res[p[i][j]] = 'B';// 剩下的全部填B
                break;
            }
    }
    if (flag) {
        puts("YES");
        cout << res << endl;
    }
    else puts("NO");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}