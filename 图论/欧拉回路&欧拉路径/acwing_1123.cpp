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
//snippet-head


//此题是trick题 由于是双向道路 所以所有点的出度都等于入度 那么肯定存在欧拉回路
//答案就是所有路径求和 除以速度即可 一个速度直接没有用

int main() {
    double x1, x2, y1, y2;
    cin >> x1 >> y1; //起点坐标没用

    double sum = 0;

    while (cin >> x1 >> y1 >> x2 >> y2) {
        double dx = x1 - x2;
        double dy = y1 - y2;

        sum += sqrt(dx * dx + dy * dy) * 2;
    }

    int minutes =  round(sum / 1000 / 20 * 60);
    int hours = minutes / 60;
    minutes %= 60;

    printf("%d:%02d\n", hours, minutes);

    return 0;
}