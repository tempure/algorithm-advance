//求 m^k mod p，时间复杂度 O(logk)。
ll qmi(ll a, ll b, int p) {
    ll res = 1; a %= p;
    while (b) {
        if (b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return res;
}
//龟速乘a * b % p 复杂度log(b)
ll powmod(ll a, ll b, ll mod) {
    ll res = 1; a %= mod;
    assert(b >= 0);
    for (; b; b >>= 1) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}
/*
快速幂求乘法逆元:
给定n组ai,pi，其中pi是质数,求ai模pi的乘法逆元返回在0∼p−1之间的逆元
b存在乘法逆元的充要条件是b与模数m互质。当模数m为质数时，b^(m-2)即为b的乘法逆元。
*/
int n;
int main() {
    cin >> n;
    int a, p;
    while (n--) {
        cin >> a >> p;
        if (__gcd(a, p) != 1) cout << "impossible" << endl;
        else cout << qmi(a, p - 2 , p) << endl;
    }
    return 0;
}