#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

int main()
{
    int n;
    scanf("%d", &n);

    LL sum = (n + 1ll) * n / 2;
    for (int i = 0; i < n - 1; i ++ )
    {
        int x;
        scanf("%d", &x);
        sum -= x;
    }

    printf("%lld\n", sum);
    return 0;
}