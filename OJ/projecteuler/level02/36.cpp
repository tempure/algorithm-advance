#include<bits/stdc++.h>
using namespace std;

bool check(int x) {
    int a[25] = {0};
    int tmp = x, cnt = 0;
    while (tmp) {
        a[++cnt] = tmp % 10;
        tmp /= 10;
    }
    for (int i = 1; i <= cnt; i++) {
        if (a[i] != a[cnt - i + 1])   return false;
    }
    tmp = x; cnt = 0;
    while (tmp) {
        a[++cnt] = tmp & 1;
        tmp >>= 1;
    }
    for (int i = 1; i <= cnt; i++) {
        if (a[i] != a[cnt - i + 1])   return false;
    }
    return true;
}

int main() {
    long long ans = 0;
    for (int i = 1; i < 1000000; i++) {
        if (check(i)) {
            cout << i << endl;
            ans += i;
        }
    }
    cout << ans << endl;
    return 0;
}