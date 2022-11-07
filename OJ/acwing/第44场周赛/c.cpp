#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n, m;
int cnt[N];

//https://www.acwing.com/activity/content/code/content/3018220/
//CF 1225D - Power Products https://codeforces.com/blog/entry/70898
//如果是x^k那么x分解质因子后每个质数的次幂都可以被k整除 
//所以 只需要凑2个每个质因子次幂加起来mod k == 0 就可以了
//具体细节见 ./p3-sol.png

int power(int a, int b)
{
    LL res = 1;
    while (b -- )
    {
        res *= a;
        if (res >= N) res = 0;
    }
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);

    LL res = 0;
    while (n -- )
    {
        int x;
        scanf("%d", &x);
        LL y = 1, z = 1;
        for (int i = 2; i * i <= x; i ++ ) //暴力分解不会超时O(sqrt(N)*N) 最快就是倍数法线性筛
            if (x % i == 0)
            {
                int s = 0;
                while (x % i == 0) x /= i, s ++ ;
                s %= m;
                if (s)
                {
                    y *= power(i, s);
                    z *= power(i, m - s);
                }
            }

        if (x > 1) y *= x, z *= power(x, m - 1);
        if (z >= N) z = 0; //超过题目最大范围直接不要了，不然cnt数组越界了，虽然那个很大的数也是满足题目要求的，但是不满足数据范围

        res += cnt[z]; //cnt[0] == 0
        cnt[y] ++ ;
    }

    printf("%lld\n", res);
    return 0;
}