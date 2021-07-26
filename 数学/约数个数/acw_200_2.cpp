#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
核心问题是求一个数的所有约数
这题主要是多组询问，如果每次都用朴素的试除求约数O(sqrt(N)) 会TLE
最后枚举所有约数代入方程检验

多组询问较快求一个数的所有约数方法：
1.先预先筛出sqrt(N)内的所有素数
2.对于一个询问，每次只试除素数分解质因数，是只试除素数，而不是暴力试除
3.DFS分解质因数的结果，求出所有约数，DFS的复杂度是约数的个数
*/

const int N = 50010;
int primes[N], cnt;
bool v[N];
int fcnt; //质因子个数
int divisor[2 * N], dcnt; //所有的约数，个数上界是2*sqrt(N)

struct Factor { //质因子分解的结果
    int p, s;
} factor[1601];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; primes[j]  <= n / i; j++) {
            v[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

void dfs(int u, int p) {
    if (u == fcnt) { //枚举到最后一个质因子了
        divisor[dcnt++] = p;
        return;
    }
    for (int i = 0; i <= factor[u].s; i++) {
        dfs(u + 1, p);
        p *= factor[u].p;
    }
}

void solve() {
    // sieve(N - 1);
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    fcnt = 0;
    int t = d;
    for (int i = 0; primes[i] <= t / primes[i]; i++) {
        int p = primes[i];
        if (t % p == 0) {
            int s =  0;
            while (t % p == 0) t /= p, s++;
            factor[fcnt++] = {p, s};
        }
    }
    if (t > 1) factor[fcnt++] = {t, 1}; //大于sqrt(N)的唯一素数因子
    dcnt = 0;
    dfs(0, 1);
    int res = 0;
    for (int i = 0; i < dcnt; i++) {
        int x =  divisor[i];
        if (gcd(a, x) == b && (ll)c / gcd(c, x) * x == d) res ++;
    }
    cout << res << endl;
}

int main() {
    sieve(N - 1);
    int t;
    cin >> t;
    while (t --) solve();
    return 0;
}