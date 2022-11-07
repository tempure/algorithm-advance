#include <bits/stdc++.h>
using namespace std;

//较好的题解：https://blog.csdn.net/justidle/article/details/106466837

/*
这个题解的意思我再详细说一下，他说的有问题，并不是和当前向量不垂直的为k1,而是同方向的为k1
就是先把所有坐标转换到x轴右侧，不影响答案，所有向量都化到最简 0向量单独算，因为不能成对
所有方向的向量都放 map 里面
然后就是枚举所有的方向向量了，每次 直接一次性 计算当前向量同向的向量，以及和当前方向向量垂直的向量
这两种所有的方案加起来的答案贡献，然后剩下的就是和当前方向不垂直的向量，这些可以乘法原理
这种计算的顺序恰好不重不漏，因为每个方向唯一，和每个方向垂直的方向也唯一

解释 2^k1 + 2^k2 -1 的 “-1” 因为只选第一个方向的时候，默认与其垂直第二个方向就选0了，同理只选第二个方向，第一个方向也选0
两种方案都不选在上面多算了一次。注意这样计算后，此时还是包含“一个都不选”这种情况的

最后的 ans + zeros - 1 里面的 “-1” 是减去一个都不选的这种非法情况
*/

const long long MOD = 1e9 + 7;

long long quick_power(long long x, long long y, long long p) {
    long long ans = 1;
    while (y) {
        if (y & 1) {
            ans = (ans * x) % p;
        }
        y >>= 1;
        x = (x * x) % p;
    }
    return ans % p;
}

int main() {
    long long n;
    long long zeros = 0;
    long long ans = 1;

    map<pair<long long, long long>, long long> m;
    map<pair<long long, long long>, long long>::iterator it;

    scanf("%lld", &n);
    for (long long i = 1; i <= n; i++) {
        long long u, v, now;
        scanf("%lld%lld", &u, &v);

        if (u == 0 && v == 0) {
            zeros++;
            continue;
        }

        now = __gcd(u, v);
        u /= now;
        v /= now;

        if (u < 0) {
            u = -u;
            v = -v;
        }
        m[make_pair(u, v)]++;
    }

    for (it = m.begin(); it != m.end(); it++) {
        if (it->second == 0) {
            continue;
        }

        long long x = it->first.first, y = it->first.second;
        long long p = quick_power(2, m[make_pair(x, y)], MOD);

        y = -y;
        if (y < 0) {
            x = -x;
            y = -y;
        }

        if (m.count(make_pair(y, x))) {
            p = (p + quick_power(2, m[make_pair(y, x)], MOD) - 1);
            m[make_pair(y, x)] = 0;
        }
        ans = (ans * p) % MOD;
    }

    printf("%lld\n", ((ans + zeros - 1) % MOD + MOD) % MOD);

    return 0;
}