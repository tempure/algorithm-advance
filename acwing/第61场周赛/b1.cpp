#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

int n;
int w[N];

//二进制枚举 (O*2^n)

int main()
{
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> w[i];

    bool res = false;
    for (int i = 0; i < 1 << n; i ++ )
    {
        int s = 0;
        for (int j = 0; j < n; j ++ )
            if (i >> j & 1)
                s += w[j];
            else
                s -= w[j];

        if (s % 360 == 0)
        {
            res = true;
            break;
        }
    }

    if (res) puts("YES");
    else puts("NO");

    return 0;
}