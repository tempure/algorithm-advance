#include <bits/stdc++.h>

#define PI 3.14159265358979323846264338327950L

//阅读理解题。。。。https://img.atcoder.jp/abc168/editorial.pdf

int main(void) {
    int a, b, h, m;
    scanf("%d%d%d%d", &a, &b, &h, &m);
    long double rad = PI * 2 * ( (long double)h / 12.0 + ((long double)m / 60.0) / 12.0 - (long double)m / 60.0);
    long double rsq = (long double)(a * a + b * b) - (long double)(2 * a * b) * cosl(rad);
    printf("%20.20Lf\n", sqrtl(rsq));
    return 0;
}