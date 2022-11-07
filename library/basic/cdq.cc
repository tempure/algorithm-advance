/*给定 n 个元素（编号 1~n），其中第 i 个元素具有 ai,bi,ci 三种属性。设 f(i) 表示满足以下 4 个条件：aj<=ai,bj<=bi,cj<=ci,j!=i的j的数量。对于 d∈[0,n)，求满足 f(i)=d 的i的数量。
输入格式:第一行n,k元素数量和最大属性值。接着n行第i行包含三个整数 ai,bi,ci。输出格式:n行每行一个整数，第 d+1行表示满足f(i)=d的i的数量。
数据范围：1<=n<=1e5,1<=ai,bi,ci<=k<=2e5
一维直接排序a 二维归并排序b 三维树状数组c,排序是三关键字排序,归并排序是为了排b，此时ab都已单调，归并过程中双指针扫描BIT查询c更新答案。
归并过程中处理了ab之后，将c插入树状数组，以c的权值建立树状数组，ci数据范围小不需要离散化。时间复杂度O(N*log^2N)*/
const int N = 100010, M = 200010;
int n, m;
struct Data {
    //res是比当前元素小的元素个数
    //s是和该元素完全相同元素的个数
    int a, b, c, s, res;
    bool operator< (const Data& t) const {
        if (a != t.a) return a < t.a;
        if (b != t.b) return b < t.b;
        return c < t.c;
    }
    bool operator== (const Data& t) const {
        return a == t.a && b == t.b && c == t.c;
    }
} q[N], w[N]; //w[]归并的临时数组
int tr[M], ans[N];
int lowbit(int x) {
    return x & -x;
}
void add(int x, int v) {
    for (int i = x; i < M; i += lowbit(i)) tr[i] += v;
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
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
        //左一半来add  右一半来查询答案
        if (q[i].b <= q[j].b) add(q[i].c, q[i].s), w[k++] = q[i++];
    //b已经有序了，所以i后边的b肯定比q[j].b都大
    //此时q[j]就可以求出符合小于c的元素个数了
        else q[j].res += query(q[j].c), w[k++] = q[j++];
    //扫描剩下的元素
    while (i <= mid) add(q[i].c, q[i].s), w[k++] = q[i++];
    while (j <= r) q[j].res += query(q[j].c), w[k++] = q[j++];
    //每次递归一层结束将左边add的树状数组清空
    for (int i = l; i <= mid; i++) add(q[i].c, -q[i].s);
    for (int i = l, j = 0; j < k; i++, j++) q[i] = w[j];
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        q[i] = {a, b, c, 1};
    }
    sort(q, q + n);
    int k = 1;
    for (int i = 1; i < n; i++) //去重记录相同元素的数量
        if (q[i] == q[k - 1]) q[k - 1].s++;
        else q[k++] = q[i];
    merge_sort(0, k - 1);
    for (int i = 0; i < k; i++)
        //res存去重之后的结果，还要加上相同的配对的s-1个
        ans[q[i].res + q[i].s - 1] += q[i].s;
    for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
    return 0;
}
/*CQOI2017《老C的任务》：二维坐标N个点M个矩形区域询问，每个点有权值，输出询问区域内点的权值和。
将所有询问和原图中的点一起处理,用z标记区分,0是原图的点,1是询问的点。对于每个询问的点(ai,aj)就是询问有多少bi<=ai && bj <= aj && zj < zi 转化为三维偏序。
用二维前缀和存每个矩阵内的元素和，标记sign为每个询问里面加上还是减去该矩阵求出子矩阵。用id来标记询问，这样才能同时处理加和减的操作，因为所有的操作都在一个数组中。
此题由于只有原图的点和询问的点，所以不用树状数组，直接用sum存左半边的结果来更新右边即可。CDQ分治复杂度O(N*logN)此题也可用专门解决高维查询的KD-Tree解决。
此题用CDQ分治不需要处理元素相同的情况 因为z维不相同。
数据范围1<=n,m<=1e5,x1<=x2,y1<=y2且为32位int范围*/
typedef long long ll;
const int N = 500010; // N + 4 * M
int n, m;
struct Data {
    //p是点权,id是查询id,sign加减符号
    int x, y, z, p, id, sign;
    ll sum;
    bool operator< (const Data& t) const {
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
        //这里的sum只是(0,0)与该点围成矩形内的和
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
        if (q[i].z)//最后处理二维前缀和
            ans[q[i].id] += q[i].sum * q[i].sign;
    for (int i = 1; i <= m;  i++) printf("%lld\n", ans[i]);
    return 0;
}
/*CQOI2011《动态逆序对》：给 1 到 n 的一个排列，按照某种顺序依次删除 m 个元素,在每次删除一个元素之前求整个序列的逆序对数。第一维是不用管的，默认就是初始序列的元素下标i,j。第二维就是元素的值a[i], a[j]。第三维设为删除元素的时间戳，从大到小分配时间戳，因为这样便于树状数组求前缀和。
因为逆序对有2种:
1. i < j && a[i] > a[j],2. i > j && a[i] < a[j]
所以分治时候要分两种情况求出来 一种是左半区间更新右边 一种是右边更新左边。对于每个元素，当前时间戳需要求出依然存在的元素和该元素互为逆序对的元素数量然后求前缀和即可*/
typedef long long ll;
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
    //ans是当前存在的和q[i].a互为逆序对的个数
    for (int i = 2; i <= n;  i++) ans[i] += ans[i - 1];
    for (int i = 0, j = n; i < m; i++, j --) printf("%lld\n", ans[j]);
    return 0;
}