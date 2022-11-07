/*
例题:给定一个非负整数序列 a，初始长度为N
有 M 个操作，有以下两种操作类型：
1、”A x”：添加操作，表示在序列末尾加一个数 x，序列的长度N增大1
2、”Q l r x”：询问操作，你需要找到一个位置 p，满足l≤p≤r，使得：a[p] xor a[p+1] xor … xor a[N] xor x 最大，输出这个最大值。
*/
//可持久化01trie + 最大异或对
//可持久化trie记录 每个子树的元素在序列中的最大位置 如果位置<l-1那就不递归这个子树
const int N = 600010; //初始长度是N 然后有M个操作 每次都可能加 最多加2倍
const int M = N * 25; //二进制表示的节点总数 1e7 < 2 ^ 25
int n, m;
int tr[M][2]; //01二进制trie
int max_id[M];//每个子树最大的点在原序列中的下标是多大
int root[N];
int s[N];
int idx;
//a[p] xor a[p + 1] xor … xor a[N] xor x 相当于 s[N] ^ x ^ s[p - 1]
//S[N] ^ x 每次可以看成一个固定值 v提前算出来,
//则相当于 求 l-1 <= p-1 <= r-1 使得 v 与 s[p-1]异或最大
//i是前缀和s下标 k当前处理的二进制位 p上一个版本 q最新版本
void insert(int i, int k, int p, int q) {
    if (k < 0) {
        max_id[q] = i;
        return;
    }
    int v = s[i] >> k & 1;
    if (p) tr[q][v ^ 1] = tr[p][v ^ 1]; //上一个版本的另外一位
    tr[q][v]  = ++idx;
    insert(i, k - 1, tr[p][v], tr[q][v]);
    max_id[q] = max(max_id[tr[q][0]], max_id[tr[q][1]]);
}
int query(int root, int c, int l) { //当前待匹配的查的值是c 左边界限制是l
    int p = root;
    for (int i = 23; i >= 0; i--) {
        int v = c >> i & 1;
        //如果二进制位相反的节点存在而且maxid满足条件
        if (max_id[tr[p][v ^ 1]] >= l) p = tr[p][v ^ 1];
        else p = tr[p][v];
    }
    return c ^ s[max_id[p]];
}
int main() {
    scanf("%d%d", &n , &m);
    max_id[0] = -1;
    root[0] = ++idx;
    insert(0, 23, 0, root[0]);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        s[i] = s[i - 1] ^ x;
        root[i] = ++idx;
        insert(i, 23, root[i - 1], root[i]);
    }
    char op[2];
    int l, r, x;
    while (m --) {
        scanf("%s", op);
        if (*op == 'A') {
            scanf("%d", &x);
            ++n;
            s[n] = s[n - 1] ^ x;
            root[n] = ++idx;
            //从最高位开始插
            insert(n, 23, root[n - 1], root[n]);
        }
        else {
            scanf("%d%d%d",  &l, &r, &x);
            printf("%d\n", query(root[r - 1], s[n] ^ x, l - 1));
        }
    }
    return 0;
}