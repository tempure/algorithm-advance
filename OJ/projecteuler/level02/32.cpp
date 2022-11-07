#include<bits/stdc++.h>
using namespace std;

//枚举每个可能的数及其可能的因子，验证即可。
//这个数不可能超过四位数，因为五位数至少由一个二位数乘三位数或一位数乘四位数得到，这样就有十个数字。
//ans = 45228

bool check(int i, int j) {
    int x[10] = {0};
    int k = i / j, cnt = 0;
    while (k) {
        if (x[k % 10])    return false;
        else            x[k % 10] = 1;
        k /= 10; cnt++;
    }
    while (j) {
        if (x[j % 10])    return false;
        else            x[j % 10] = 1;
        j /= 10; cnt++;
    }
    while (i) {
        if (x[i % 10])    return false;
        else            x[i % 10] = 1;
        i /= 10; cnt++;
    }
    return cnt == 9 && x[0] == 0;
}

int main() {
    int ans = 0;
    for (int i = 1; i <= 9999; i++) {
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0 && check(i, j)) {
                ans += i;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}