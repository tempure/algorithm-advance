#include<bits/stdc++.h>
using namespace std;

long long maxx, x;

//暴力枚举check, x < 10000
// ans = 932718654

void check() {
    int num[10] = {0}, cnt = 0, tmp = x;
    num[0] = 1;
    while (tmp) {
        if (num[tmp % 10] == 0) cnt++;
        else                return;
        num[tmp % 10] = 1;
        tmp /= 10;
    }
    if (cnt == 9) {
        maxx = max(maxx, x);
    }
}

int main() {
    for (int i = 1; i <= 9999; i++) {
        x = 0;
        for (int j = 1, tmp, mul = 1; j <= 9; j++) {
            tmp = i * j;
            while ((x * mul + tmp) / mul != x)   mul *= 10;
            x = x * mul + tmp;
            if (x > 1e9)  break;
            check();
        }
    }
    cout << maxx << endl;
    return 0;
}