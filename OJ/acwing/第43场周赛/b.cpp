#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 200010;
int n;
LL S;
int a[N];


//推公式

//区间交集的元素个数
int get(LL a, LL b, LL c, LL d) {
    return min(b, d) - max(a, c) + 1;
}

int main() {
    scanf("%d%lld", &n, &S);
    LL sum = 0;
    for (int i = 1; i <= n; i ++ ) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    for (int i = 1; i <= n; i ++ )
        printf("%d ", a[i] - get(1, a[i], S - (sum - a[i]), S - (n - 1)));

    return 0;
}