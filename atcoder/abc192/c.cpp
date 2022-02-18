#include<stdio.h>
int f(int n) {
    int c[20] = {};
    while (n) {
        c[n % 10]++;
        n /= 10;
    }
    int g1 = 0, g2 = 0;
    for (int i = 9; i >= 0; i--)for (int j = 0; j < c[i]; j++)g1 = g1 * 10 + i;
    for (int i = 0; i <= 9; i++)for (int j = 0; j < c[i]; j++)g2 = g2 * 10 + i;
    return g1 - g2;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++)n = f(n);
    printf("%d\n", n);
}
