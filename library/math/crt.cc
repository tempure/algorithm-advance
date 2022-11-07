//中国剩余定理模板
const int N = 11;
int n;
int A[N], B[N];
void exgcd(ll a, ll b, ll &x, ll & y) {
    if (!b)
        x = 1, y = 0;
    else {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}
int main() {
    scanf("%d", &n);
    ll M = 1;
    //方程组为 x 同余 B[i] mod (A[i])
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &A[i], &B[i]);
        M *= A[i];
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll Mi = M / A[i];
        //求Mi*ti 同余 1(mod mi) 的ti
        ll ti, x;
        exgcd(Mi, A[i], ti, x);
        res += (B[i] * Mi * ti);
    }
    //中国剩余定理给出的通解是 x + k * M 对M取模即可得到最小正整数解
    cout << (res % M + M )  % M << endl;
}