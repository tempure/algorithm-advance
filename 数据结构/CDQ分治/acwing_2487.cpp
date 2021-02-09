#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
将所有询问和原图中的点一起处理 用z标记区分 0是原图的点 1是询问的点
对于每个询问的点(ai,aj) 就是询问有多少bi<=ai && bj <= aj && zj < zi 转化为三维偏序
用二维前缀和存每个矩阵内的元素和，标记sign为每个询问里面加上还是减去该矩阵求出子矩阵
用id来标记询问，这样才能同时处理加和减的操作，因为所有的操作都在一个数组中

此题由于只有原图的点和询问的点，所以不用树状数组，直接用sum存左半边的结果来更新右边即可
CDQ分治复杂度O(N*logN) 此题也可用专门解决高维查询的KD-Tree解决
*/

const int N = 500010; // N + 4 * M

int n, m;

struct Data {
    int x, y, z, p, id, sign; //z=0表示原图的点 1代表查询 p是点权 id是查询id sign加减符号
    ll sum;

    bool operator< (const Data&  t) const {
        if (x != t.x) return x < t.x;
        if (y != t.y) return y < t.y;
        return z < t.z;
    }
} q[N], w[N]; //w辅助数组

ll ans[N];

void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(l, mid), merge_sort(mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    ll sum = 0;
    while (i <= mid && j <= r)
        //直接用sum来存即可 只有0/1两种情况
        if (q[i].y <= q[j].y) sum += !q[i].z * q[i].p, w[k++] = q[i++];
        else q[j].sum += sum, w[k++] = q[j++];
    while (i <= mid) sum += !q[i].z * q[i].p, w[k++] = q[i++];
    while (j <= r) q[j].sum += sum, w[k++] = q[j++];
    for (int i = l, j = 0; j < k; i++, j++) q[i] = w[j];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int x, y, p;
        scanf("%d%d%d", &x, &y, &p);
        q[i] = {x, y, 0, p};
    }
    int k = n; //将询问也存进q[]
    for (int i = 1; i <= m; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        q[k++] = {x2, y2, 1, 0, i, 1};
        q[k++] = {x1 - 1, y2, 1, 0, i, -1}; //减去的矩形
        q[k++] = {x2, y1 - 1, 1, 0, i, -1};
        q[k++] = {x1 - 1, y1 - 1, 1, 0, i, 1};
    }

    sort(q, q + k);
    merge_sort(0, k - 1);

    for (int i = 0; i < k; i++)
        if (q[i].z)
            ans[q[i].id] += q[i].sum * q[i].sign;

    for (int i = 1; i <= m;  i++) printf("%lld\n", ans[i]);
    return 0;
}