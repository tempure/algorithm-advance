#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 300010;

char s[N];

int main()
{
    scanf("%s", s);

    LL res = 0;
    for (int i = 0; s[i]; i ++ )
    {
        if (s[i] % 4 == 0) res ++ ;
        if (i && (s[i - 1] * 10 + s[i]) % 4 == 0)
            res += i;
    }

    printf("%lld\n", res);
    return 0;
}