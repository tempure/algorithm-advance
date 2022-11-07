#include <bits/stdc++.h>

using namespace std;

inline int gi()
{
    int f = 1, x = 0; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return f * x;
}

const int N = 103, M = N << 1;

int n, k;
int a[N], b[N];

int main()
{
    n = gi(), k = gi();
    for (int i = 1; i <= k; i += 1)
    {
        int d = gi();
        for (int j = 1; j <= d; j += 1)
            a[j] = gi(), ++b[a[j]];
    }
    int cnt = 0;
    for (int i = 1; i <= n; i += 1) cnt += (b[i] == 0);
    cout << cnt << endl;
    return 0;
}