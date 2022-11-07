#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

typedef long long LL;

const int N = 300010;

// refer to the ./c_sol.png
// 奇数偶数分开放在哈希表中快速查

int n;
int q[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &q[i]);

    LL res = 0, sum = 0;
    unordered_map<int, int> s[2];
    s[0][sum] ++ ;
    for (int i = 1; i <= n; i ++ ) {
        sum ^= q[i];
        res += s[i & 1][sum];
        s[i & 1][sum] ++ ;
    }

    printf("%lld\n", res);
    return 0;
}