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

//https://www.bilibili.com/video/BV1aF411N77V?t=1404.1
//决策单调性 + 贪心 O(N)
//先将序列排序来看
//结论1: 最优选法的集合一定是此序列的某个前缀+后面某一个比较大的数
//结论2: 前缀选的最后一个数一定是满足此数小于前缀+后面数的平均数, 下一个数一定大于平均数
//结论3: 对于后面较大的数w[i], 如果w[i]对应能选最长前缀的最后一个数是w[k], 那么对于w[i+1]来说对应前缀一定比k长
//因为把w[i]换成w[i+1], 此时前缀加上w[i+1]的平均数只会变大，从而w[k]还是肯定小于平均数的，那么对于w[i+1]来说，只需要从
//k开始往后枚举寻找其对应的最长前缀，后面的大数对应的前缀长度是有单调性的。
//最后的最大值是根据后面的大数来划分求的

const int N = 5e5 + 10;
int n, m; //n当前有序序列长度
int w[N];

void solve() {
    cin >> m;
    double res = 0, sum = 0; //sum 前缀和
    int k = 0;
    while (m --) {
        int op, x;
        cin >> op;
        if (op == 1) {
            cin >> x;
            w[++n] = x;
            //对于当前的最后一个w[n], 求出最长前缀
            while (k + 1 <= n && w[k + 1] <= (sum + w[n]) / (k + 1))
                sum += w[++k]; //看看下一个数是否小于平均数，小于就选上
            res = max(res, w[n] - (sum + w[n]) / (k + 1));
        }
        else {
            printf("%lf\n", res);
        }
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}