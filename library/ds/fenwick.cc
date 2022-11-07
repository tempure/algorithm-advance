//树状数组 区间查询/单点修改
/*
给定长度为N的数列A，然后输入M行操作指令。
第一类指令形如“C l r d”，表示把数列中第l~r个数都加d。
第二类指令形如“Q X”，表示询问数列中第x个数的值。
对于每个询问，输出一个整数表示答案。
*/
const int N = 1e5 + 10;
int n, m;
int a[N];
ll tr[N];
int lowbit(int x) {
    return x & -x;
}
void add(int x , int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}
ll sum(int x) {
    ll res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1 ; i <= n; i++) scanf("%d", &a[i]);
    //初始化差分数组 暴力方法建树
    //查询某个数就是直接求和即可
    //所需的操作就是差分数组的单点修改 区间查询
    for (int i = 1; i <= n; i++) add(i, a[i] - a[i - 1]);
    while (m --) {
        char op[2];
        int l, r, d;
        scanf("%s%d", op, &l);
        if (*op == 'C') {
            scanf("%d%d", &r, &d);
            add(l, d); add(r + 1, -d);
        }
        else {
            printf("%lld\n", sum(l));
        }
    }
    return 0;
}
/*
例题:如果三个点(i,yi),(j,yj),(k,yk)满足1<=i<j<k<=n且yi>yj,yj<yk，则称这三个点构成V图腾;
如果三个点(i,yi),(j,yj),(k,yk)满足1<=i<j<k<=n且yi<yj,yj>yk，则称这三个点构成^图腾;
第一行一个数n。第二行是n个数，分别代表y1，y2,…,yn。
输出：两个数，中间用空格隔开，依次为V的个数和^的个数。
*/
//依次枚举每个点为最低点或者最高点
//从然后划分为左边和右边 计算左边有多少个y比当前点的y高或者低  左右乘起来就是当前集合的总数、
//求出所有点代表的集合 然后求和即可
//在这个过程中 扫描到一个y比当前y大的点 那么当前y增加1 还需要统计区间和2个功能就可以用树状数组实现了
const int N = 200010;
int n;
int a[N];
int tr[N]; //树状数组
int gr[N], lo[N]; //每个位置前面的位置 有多少位置的高度比当前位置的高度高 / 低
int lowbit(int x) {
    return x & -x;
}
void add(int x, int c) { //单点增加 修改全部父结点
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}
int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}
/*
从左向右依次遍历每个数a[i]，使用树状数组统计在i位置之前所有比a[i]大的数的个数、以及比a[i]小的数的个数。
统计完成后，将a[i]加入到树状数组。
原理就是把tr[]下标当作高度，要把位置i看成横坐标的话，那么高度就得看成纵坐标，从左往右扫的时候只会求出这个点左边比自己小的和大的
第二次从右往左扫之前要先清空树状数组，然后重新扫 不然会重复 但是左边的结果已经存在了gr和lo数组中.
*/
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        int y = a[i]; //当前点的高度
        gr[i] = sum(n) - sum(y);
        lo[i] = sum(y - 1);
        add(y, 1);
    }
    //清空 然后倒着扫一次
    memset(tr, 0, sizeof tr);
    ll res1 = 0, res2 = 0; //v以及^
    for (int i = n; i; i--) {
        int y = a[i];
        res1 += gr[i] * 1ll * (sum(n) - sum(y));
        res2 += lo[i] * 1ll * (sum(y - 1));
        add(y, 1);
    }
    printf("%lld %lld\n", res1, res2);
    return 0;
}
/*
例题:有n头奶牛，已知它们的身高为 1~n 且各不相同，但不知道每头奶牛的具体身高。
现在这n头奶牛站成一列，已知第i头牛前面有Ai头牛比它低，求每头奶牛的身高。
输入n，第2..n行：每行输入一个整数Ai,第i行表示第i头牛前面有Ai头牛比它低。
（注意：因为第1头牛前面没有牛，所以并没有将它列出）
*/
//从后往前扫 i位置的排名就是剩下的牛里面a[i] + 1 剩下是指前面没扫的包括当前位置的牛
//本质问题就是从剩余的数中找出第k小的数 以及删除某一个数的操作
//用tr[]数组的下标表示高度 所有元素置为1表示还没被删，从后往前扫
//对于每个a[i]也就是第k高 当tr[j]的前缀和等于a[i]的时候，也就是这时候的下标j就是答案
const int N = 100010;
int n; int a[N];
int ans[N];
int tr[N];
int lowbit(int x) {
    return x & -x;
}
void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}
int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}
int main() {
    scanf("%d", &n);
    //这里第一个0不读入默认0
    for (int i = 2; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) add(i, 1); //初始化树状数组
    for (int i = n; i; i--) {
        int k = a[i] + 1;
        //二分
        int l = 1, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (sum(mid) >= k) r = mid;
            else l = mid + 1;
        }
        ans[i] = r;
        add(r, -1);
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}
/*树状数组求逆序对
整数范围 显然要先离散化才能在树状数组add
由于会出现相同的元素，而且std::sort是不稳定排序
离散化之后的数是没有相同的，相同元素必须保持原来插入的顺序，不然会错
此时要用双关键字排序 保证了插入顺序在离散化之后也是递增
每次统计即可，比如现在遍历插入的第8个数，那么加上比当前数大的数的个数即可
*/
#define x first //元素的值
#define y second //第几个加入的
typedef pair<int, int> pii;
const int N = 100003;
pii a[N]; //所有的点 双关键字排序
int tr[N], rk[N]; //rk是离散化映射
int n;
//双关键字排序 值相同的按照加入顺序升序
bool cmp(pii a, pii b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
int lowbit(int x) {
    return x & -x;
}
void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}
ll sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x; //x是val值
        a[i].y = i; //加入的顺序
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        rk[a[i].y] = i;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        add(rk[i], 1);
        ans += i - sum(rk[i]);
    }
    cout << ans << endl;
    return 0;
}