#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
动态逆序对 三位偏序 CDQ分治离线处理

第一维是不用管的，默认就是初始序列的元素下标i,j
第二维就是元素的值a[i], a[j]
第三维设为删除元素的时间戳，从大到小分配时间戳，因为这样便于树状数组求前缀和

因为逆序对有2种:
1. i < j && a[i] > a[j]
2. i > j && a[i] < a[j]
所以分治时候要分两种情况求出来 一种是左半区间更新右边 一种是右边更新左边

对于每个元素，当前时间戳需要求出依然存在的元素和该元素互为逆序对的元素数量
然后求前缀和即可
*/

const int N = 100010;

int n, m;
struct Data {
    int a, t, res;
} q[N], w[N];

int tr[N], pos[N];
ll ans[N];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int v) {
    for (int i = x; i < N; i += lowbit(i)) tr[i] += v;
}

int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(l, mid), merge_sort(mid + 1, r);

    //第一种逆序 左边更新右边
    int i = mid, j = r;
    while (i >= l && j > mid)
        if (q[i].a > q[j].a) add(q[i].t, 1), i --;
        else q[j].res += query(q[j].t - 1), j --;
    while (j > mid) q[j].res += query(q[j].t - 1), j --;
    for (int k = i + 1; k <= mid; k++) add(q[k].t, - 1);

    //第二种逆序 用右边更新左边
    j = l, i = mid + 1;
    while (j <= mid && i <= r)
        if (q[i].a < q[j].a) add(q[i].t, 1), i++;
        else q[j].res += query(q[j].t - 1), j++;
    while (j <= mid) q[j].res += query(q[j].t - 1), j++;
    for (int k = mid + 1; k < i; k++) add(q[k].t, -1);

    //归并
    i = l, j = mid + 1;
    int k = 0;
    while (i <= mid && j <= r)
        if (q[i].a <= q[j].a) w[k ++ ] = q[i ++ ];
        else w[k ++ ] = q[j ++ ];
    while (i <= mid) w[k ++ ] = q[i ++ ];
    while (j <= r) w[k ++ ] = q[j ++ ];

    for (i = l, j = 0; j < k; i ++, j ++ ) q[i] = w[j];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i].a);
        pos[q[i].a] = i;
    }
    for (int i = 0, j = n; i < m; i++) {
        int a;
        scanf("%d", &a);
        q[pos[a]].t = j --; //逆序分配时间戳
        pos[a] = -1;
    }
    for (int i = 1, j = n - m; i <= n; i++) {
        if (pos[i] != -1)
            q[pos[i]].t = j --;
    }

    merge_sort(0, n - 1);

    for (int i = 0; i < n; i++) ans[q[i].t] = q[i].res;
    for (int i = 2; i <= n;  i++) ans[i] += ans[i - 1]; //ans是当前存在的和q[i].a互为逆序对的个数
    for (int i = 0, j = n; i < m; i++, j --) printf("%lld\n", ans[j]);

    return 0;
}