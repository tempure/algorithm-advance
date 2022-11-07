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
//void 版本
void exgcd(ll a, ll b, ll &x, ll & y) {
    if (!b)
        x = 1, y = 0;
    else {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}
/*ax同余b(mod m)的最小正整数解是(x*b/d%(m/d)+(m/d))%(m/d)
通解是x0 + k * (m/d), d是gcd(a,m)*/
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
        else cout << (ll)x * (b / d) % (m / d) << endl;
        //如果直接用int存再取模 答案错误 因为int会溢出
    }
    return 0;
}