#include <bits/stdc++.h>
using namespace std;

//exgcd模板 求出 ax+by = gcd(a,b)的 x,y
// long long 返回 gcd(a,b)
ll exgcd(ll a, ll b, ll &x, ll & y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

//int 返回 gcd(a,b)
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

//void 版本 只求x,y
void exgcd(ll a, ll b, ll &x, ll & y) {
    if (!b)
        x = 1, y = 0;
    else {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}

//一般的线性同余方程
//a*x≡b(mod m)，如果无解则输出 impossible。
typedef long long ll;
int n;

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y  = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

int main() {
    cin >> n;
    int a, b , m;
    int x, y;
    while (n --) {
        cin >> a >> b >> m;
        int d = exgcd(a, m, x, y);
        if (b % d) puts("impossible");
        else cout << (ll)x * (b / d) % (m / d) << endl; //  乘的结果可能爆int 所以用long long 存储之后再取模
        //如果直接用int存再取模 答案错误 因为int会溢出 注意模数 m / gcd(a, m) 都是和特解x 同余的 也可以直接模m
    }
    return 0;
}