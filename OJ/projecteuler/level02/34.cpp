#include<bits/stdc++.h>
using namespace std;

//先估值上界: f(n) = 10^n，g(n) = 9！*n
// n = 7
// max_val = 2540160

int f[10];

bool check(int x) {
    int tmp = x, ans = 0;
    while (x) {
        ans += f[x % 10];
        x /= 10;
    }
    return ans == tmp;
}

int main() {
    f[0] = 1;
    for (int i = 1; i <= 9; i++) {
        f[i] = f[i - 1] * i;
    }
    long long ans = 0;
    for (int i = 10; i <= 2500000; i++) {
        if (check(i)) {
            ans += i;
        }
    }
    cout << ans << endl;
    return 0;
}