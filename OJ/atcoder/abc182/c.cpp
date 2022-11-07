#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

//https://atcoder.jp/contests/abc182/editorial/324
//分类讨论

int main() {
    int64_t n;
    scanf("%" SCNd64, &n);

    int cnt[3] = { 0 };
    while (n) {
        cnt[n % 10 % 3]++;
        n /= 10;
    }
    int cur = (cnt[1] + 2 * cnt[2]) % 3;
    int k = cnt[0] + cnt[1] + cnt[2];
    int res;
    if (!cur) res = 0;
    else if (cur == 1) {
        if (cnt[1]) {
            if (k == 1) res = -1;
            else res = 1;
        } else {
            if (k == 2) res = -1;
            else res = 2;
        }
    } else {
        if (cnt[2]) {
            if (k == 1) res = -1;
            else res = 1;
        } else {
            if (k == 2) res = -1;
            else res = 2;
        }
    }
    printf("%d\n", res);

    return 0;
}