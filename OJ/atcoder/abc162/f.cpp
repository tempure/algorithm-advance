#include <iostream>
#include <cstdio>
using namespace std;
long long n;
long long a[200010];
long long dp[200010];
long long sum[200010];

//https://www.cnblogs.com/zcr-blog/p/12717719.html
//dp[i]代表前i个数取 i/2 个数的最大值，显然dp[1]=0
/*
若i为奇数:则若不选i，答案是dp[i-1]，若选i，答案是dp[i-2]+a[i]，在两者之间取max即可
若i为偶数:若选i同上，若不选i只有取i-1以内左右编号为奇数的数这一种情况，两者取max即可。
*/

int main() {
    scanf("%lld", &n);
    for (long long i = 1; i <= n; i++) scanf("%lld", &a[i]);
    sum[1] = a[1];
    for (long long i = 3; i <= n; i += 2) {
        sum[i] = sum[i - 2] + a[i];
    }
    for (long long i = 2; i <= n; i++) {
        if (i & 1) {
            dp[i] = max(dp[i - 1], dp[i - 2] + a[i]);
        } else {
            dp[i] = max(sum[i - 1], dp[i - 2] + a[i]);
        }
    }
    printf("%lld", dp[n]);
    return 0;
}