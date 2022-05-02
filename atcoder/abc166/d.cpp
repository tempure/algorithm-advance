#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int gi()
{
    int f = 1, x = 0; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return f * x;
}

const int N = 100003, M = N << 1;

int n, k;
LL fac5[N];

int main()
{
    n = gi();
    LL now = 1;
    for (int i = 1; i <= 20000; i += 1)
    {
        now = 1;
        for (int j = 1; j <= 5; j += 1) now *= (i - 7778);
        fac5[i] = now;
    }
    for (int i = -7777; i <= 7777; i += 1)
        for (int j = -7777; j <= 7777; j += 1)
            if (fac5[i + 7778] - fac5[j + 7778] == n)
            {
                printf("%d %d\n", i, j);
                return 0;
            }
    return 0;
}