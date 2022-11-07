#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

// p/q 在 b 进制下为k位有限小数 <==> p/q * b^k 为整数 <==> q | b^k

/*
考虑到 1e18 的数据范围, 判断 q 能否整除 b^k, 本质就是看 q 是否是 b 的质因子组合相乘的
每次求 gcd(q, b), 然后 q/(gcd(q,b)) 直到最后判断是否 q == 1 即可
*/

//https://www.acwing.com/video/3978/

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T -- ) {
        LL p, q, b;
        scanf("%lld%lld%lld", &p, &q, &b);
        LL d = gcd(p, q);
        q /= d;
        while (q > 1) {
            d = gcd(q, b);
            if (d == 1) break;
            while (q % d == 0) q /= d; //优化，不然会T, 每次除完所有的 gcd
        }

        if (q == 1) puts("YES");
        else puts("NO");
    }

    return 0;
}