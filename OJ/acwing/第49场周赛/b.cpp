#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//https://www.acwing.com/solution/content/97764/

const int INF = 1e8;

int main()
{
    int n;
    scanf("%d", &n);

    int sum = 0;
    int a = -INF, b = INF;
    while (n -- )
    {
        int x;
        scanf("%d", &x);
        if (x > 0) sum += x;
        if (x < 0 && x % 2) a = max(a, x);
        if (x > 0 && x % 2) b = min(b, x);
    }

    if (sum % 2) printf("%d\n", sum);
    else printf("%d\n", max(sum + a, sum - b));

    return 0;
}