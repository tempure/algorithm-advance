#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

//正面-反面 排序 贪心

int n, k, ans;
struct node {
    int a, b;
} q[200010];

bool cmp (node x, node y) {
    return x.a - x.b > y.a - y.b; //按变小的幅度从大到小排序。
}

int main() {
    scanf ("%d%d", &n, &k);
    for (int i = 1; i <= n; i ++ )
        scanf ("%d", &q[i].a);
    for (int i = 1; i <= n; i ++ )
        scanf ("%d", &q[i].b);
    sort(q + 1, q + n + 1, cmp);
    k = n - k;
    for (int i = 1; i <= n; i ++ ) {
        if (q[i].b < q[i].a && k > 0) {
            ans += q[i].b;
            k --;
        } else ans += q[i].a;
    }
    printf("%d", ans);
    return 0;
}
