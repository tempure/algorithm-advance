/*给定 n 个区间 [ai,bi]和 n 个整数 ci。
你需要构造一个整数集合 Z，使得∀i∈[1,n],Z 中满足ai<=x<=bi的整数 x 不少于 ci 个。
求这样的整数集合 Z 最少包含多少个数
第一行包含整数 n
接下来n行，每行包含三个整数ai,bi,ci*/
//题意有点绕：从0~50000中选出尽量少的数，使得每个区间[ai,bi]都至少ci个数被选, 求选出数的个数
//求最小值那么就是最长路问题了 题目保证有解 就不用判断正环了
//设s[i] 为1到i中被出的数的个数 也就是前i个数 dist[i] 同理 最后答案是dist[50001]
//需要满足: s[i] >= s[i - 1], s[i] - s[i - 1] <= 1, s[b] - s[a-1] >= c
const int N = 50010, M = 150010;
int n;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int q[N];
bool st[N];
void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}
void spfa() {
    memset(dist, 0xcf, sizeof dist);
    int hh = 0, tt = 1;
    q[0] = 0;
    dist[0] = 0;
    st[0] = true;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] =  dist[t] + w[i];
                if (!st[j]) {
                    q[tt ++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
}
int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= 50001; i++) {
        add(i - 1, i , 0);
        add(i, i - 1, -1);
    }
    while (n --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a ++; b++;
        add(a - 1, b, c);
    }
    spfa();
    printf("%d\n", dist[50001]);
    return 0;
}
/*
例题:排队布局
第一行包含三个整数 N,ML,MD。
接下来 ML 行，每行包含三个正整数 A,B,L，表示奶牛 A 和奶牛 B 至多相隔 L 的距离。
再接下来 MD 行，每行包含三个正整数 A,B,D，表示奶牛 A 和奶牛 B 至少相隔 D 的距离。
输出一个整数，如果不存在满足要求的方案，输出-1；如果 1 号奶牛和 N 号奶牛间的距离可以任意大，输出-2；否则，输出在满足所有要求的情况下，1 号奶牛和 N 号奶牛间可能的最大距离。
*/
//第一个就是判负环 全部加入队列跑一次SPFA即可
//所有奶牛的距离都是相对距离，所以需要虚拟原点，假设所有牛都在数轴的正半轴 所有点都在x0的左边 也就是说x0是最右边的
//对于第二个要求 直接把1号点固定在0 也就是 x1 = 0 因为都是相对距离 不影响距离 最后看一下xn是不是可以无限大 这也等价于1号点到其他点的最短距离
//求一下xn的最短路 如果无穷大 就是无穷大 否则就是最大值
//约束条件：xi <= x[i+1] + 0, xb <= xa + l, xa <= xb - d
const int INF = 0x3f3f3f3f;
const int N = 1010, M = 21010;  //边数判断就是满足条件的类 每类需要多少点 全部加起来
//因为加边 的时候 会满足所有条件 也就是说每个条件 都要单独加边
int q[N], h[N], e[M], ne[M], idx, w[M], cnt[N], dist[N];
bool st[N];
int n, m1, m2;
void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}
bool spfa(int sz) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    int hh = 0, tt = 1;
    for (int i = 1; i <= sz; i++) { //加入队列 求负环
        dist[i] = 0;
        q[tt++] = i;
        st[i] = true;
    }
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n)  return false;
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return true;
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 1; i < n; i++) add(i + 1, i, 0);
    while (m1 --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (b < a ) swap(a, b);
        add(a, b, c);
    }
    while (m2 --) {
        int a, b , c;
        scanf("%d%d%d", &a, &b, &c);
        if (b < a) swap(a, b);
        add(b, a, -c);
    }
    if (!spfa(n)) puts("-1"); //前n个点的图有负环
    else {
        spfa(1); //将第一个点放进去求
        if (dist[n] == INF) puts("-2");
        else printf("%d\n", dist[n]);
    }
    return 0;
}