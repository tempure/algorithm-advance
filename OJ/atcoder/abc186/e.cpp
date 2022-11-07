#include <bits/stdc++.h>
using namespace std;
#define int long long


//S + x * K = y * N
//-> K*x ≡ S (mod N)
//然后套模板求最小整数解即可

//求x, y，使得ax + by = gcd(a, b)
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d; //最大公约数
}

void solve() {
    int n, s, k;
    cin >> n >> s >> k;
    if (s % __gcd(n, k)) puts("-1");
    else {
        int x, y;
        int d = exgcd(k, n, x, y);
        x *= -1;//一定要注意 x 式子里面的正负号
        cout << (x * (s / d) % (n / d) + (n / d)) % (n / d) << endl;
    }
}

signed main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}