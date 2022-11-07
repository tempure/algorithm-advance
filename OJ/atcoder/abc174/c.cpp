#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define M 10000001

//真就直接暴力啊。。。
//https://www.cnblogs.com/poi-bolg-poi/p/13423425.html

int n, now;
bool flag;

int main() {
    scanf("%d", &n);
    for (int i = 1; i < M; ++i) {
        now = (1ll * now * 10 % n + 7) % n;
        if (now == 0) {
            printf("%d\n", i);
            flag = true; break;
        }
    }
    if (!flag) puts("-1");
    return 0;
}