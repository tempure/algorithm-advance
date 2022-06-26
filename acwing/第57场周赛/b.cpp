#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

//https://www.acwing.com/solution/content/122237/
//乘一次然后一直sqrt是最优的
//边乘边开根一定次数更多，因为乘机次数增加不可避免，开根次数取决于分解质因数后最高因子次幂

int main()
{
    int n;
    cin >> n;

    int res = 1, m = 0;
    vector<int> a;

    for (int i = 2; i * i <= n; i ++ )
        if (n % i == 0)
        {
            int c = 0;
            while (n % i == 0) n /= i, c ++ ;
            res *= i;
            a.push_back(c);
            while (1 << m < c) m ++ ;
        }

    if (n > 1)
    {
        res *= n;
        a.push_back(1);
        while (1 << m < 1) m ++ ;
    }

    for (auto x : a) //至少要乘一次
        if (x < 1 << m)
        {
            m ++ ;
            break;
        }

    cout << res << ' ' << m << endl;

    return 0;
}