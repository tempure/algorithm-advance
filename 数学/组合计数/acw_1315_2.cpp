#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int primes[N], cnt;
bool st[N];
int a[N], b[N];

void seive(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int get(int n, int p) {
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}

void mul(int r[], int &len, int x) {
    int t = 0;
    for (int i = 0; i < len; i ++ ) {
        t += r[i] * x;
        r[i] = t % 10;
        t /= 10;
    }
    while (t) r[len++] = t % 10, t /= 10;
}

void sub(int a[], int al, int b[], int bl) {
    for (int i = 0, t = 0; i < al; i++) {
        a[i] -= t + b[i];
        if (a[i] < 0) a[i] += 10, t = 1;
        else t = 0;
    }
}

int C(int x, int y, int r[]) {
    int len = 1;
    r[0] = 1;
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        int s = get(x, p) - get(y, p) - get(x - y, p);
        while (s --) mul(r, len, p); // p^s
    }
    return len;
}

void solve() {
    seive(N - 1);
    int n, m;
    cin >> n >> m;
    int al = C(n + m, n, a);
    int bl = C(n + m, m - 1, b);
    sub(a, al, b, bl);
    int k = al - 1;

    while (!a[k] && k > 0) k --;
    while (k >= 0) printf("%d", a[k--]);
}

int main() {
    solve();
    return 0;
}