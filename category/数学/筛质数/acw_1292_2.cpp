#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int p[N];
bool v[N];
int n, cnt;

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!v[i]) p[cnt++] = i;
        for (int j = 0; p[j] <= n / i; j++) {
            v[p[j] * i] = true;
            if (i % p[j] == 0) break;
        }
    }
}

void solve() {
    sieve(N);
    while (cin >> n && n) {
        bool flag = false;
        for (int i = 3; i < n; i++) {
            if (!v[i] && !v[n - i]) {
                flag = true;
                cout << n << " = " << i << " + " << n - i << endl;
                break;
            }
        }
        if (flag == false) puts("Goldbach's conjecture is wrong.");
    }
}

int main() {
    solve();
    return 0;
}