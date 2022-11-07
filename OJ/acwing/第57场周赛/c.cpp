#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1000010;

int n;
LL s[N];
int stk[N];

//https://www.acwing.com/video/4001/

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        int x;
        scanf("%d", &x);
        s[i] = s[i - 1] + x - 100;
    }

    int top = 0, res = 0;
    stk[ ++ top] = 0;
    for (int i = 1; i <= n; i ++ )
    {
        if (s[stk[top]] > s[i]) stk[ ++ top] = i;
        else if (s[stk[top]] < s[i])
        {
            int l = 1, r = top;
            while (l < r)
            {
                int mid = l + r >> 1;
                if (s[stk[mid]] <= s[i]) r = mid; //这里应该是 <= 因为必须前缀和 > 0, 只写 < 不能正确处理 s[i] == s[stk[mid]]
                else l = mid + 1;
            }
            res = max(res, i - stk[r]);
        }
    }

    printf("%d\n", res);
    return 0;
}