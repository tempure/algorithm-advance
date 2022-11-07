#include <bits/stdc++.h>
using namespace std;

//https://www.acwing.com/video/3621/

/*
给定两个正整数 a 和 b。

你需要回答 q 个询问。

每个询问给定两个整数 l,r，你需要找到最大的整数 x，满足：
x  是 a 和 b 的公约数。
l≤x≤r。

所有测试点满足 1≤a,b≤1e9，1≤q≤1e4，1≤l≤r≤1e9。
*/

//定理：a,b的所有公约数，一定是gcd(a,b)的约数

vector<int> get_divisors(int x) {
    vector<int> res;
    for (int i = 1; i <= x / i; i ++ )
        if (x % i == 0) {
            res.push_back(i);
            if (i != x / i) res.push_back(x / i);
        }

    sort(res.begin(), res.end());
    return res;
}

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    int d = __gcd(a, b);

    auto ds = get_divisors(d);
    int q;
    scanf("%d", &q);

    while (q -- ) {
        int L, R;
        scanf("%d%d", &L, &R);

        int l = 0, r = ds.size() - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (ds[mid] <= R) l = mid;
            else r = mid - 1;
        }

        int x = ds[r];
        if (x >= L && x <= R) printf("%d\n", x);
        else puts("-1");
    }

    return 0;
}