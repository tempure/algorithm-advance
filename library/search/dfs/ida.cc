/*
给定n本书，编号为1-n。在初始状态下，书是任意排列的。在每一次操作中，可以抽取其中连续的一段，再把这段插入到其他某个位置。把书按照1-n的顺序依次排列。求最少操作。
输入格式
第一行包含整数T，表示共有T组测试数据。每组数据包含两行，第一行为整数n，表示书的数量。
第二行为n个整数，表示1-n的一种任意排列。同行数之间用空格隔开。
输出格式
每组数据输出一个最少操作次数。
如果最少操作次数大于或等于5次，则输出”5 or more”。
每个结果占一行。
数据范围
1 <= n <= 15
输入样例：
3
6
1 3 4 6 2 5
5
5 4 3 2 1
10
6 8 5 3 4 7 2 9 1 10
输出样例：
2
3
5 or more
*/
//后继关系:n和n + 1 互为后继
//将任意一段改变位置，整个当前的序列后继关系 将被改变3个
//假设所有的错误的后继关系有tot个 估价函数就是tot / 3 上取整 也就是(tot + 2) / 3 下取整
//一个升序的序列 tot就是0 那么估价函数的值就是0
const int N = 15;
int n;
int q[N];
int w[5][N];
int f() {
    int tot = 0;
    for (int i = 0; i + 1 < n; i++)
        if (q[i + 1] != q[i] + 1)
            tot ++;
    return (tot + 2) / 3;
}
bool dfs(int depth, int max_depth) {
    if (depth + f() >  max_depth) return false;
    if (f() == 0) return true;
    for (int len = 1; len <= n; len++) //区间长度
        for (int l = 0; l + len - 1 < n; l++) { //枚举区间起点
            int r = l + len - 1;
            for (int k = r + 1; k < n; k++) { //将当前区间放到k位置的后面,枚举k从r + 1开始
                //备份状态
                memcpy(w[depth], q, sizeof q);
                int y = l;
                for (int x = r + 1; x <= k; x ++, y ++) q[y] = w[depth][x];
                for (int x = l; x <= r; x ++, y ++) q[y] = w[depth][x];
                if (dfs(depth + 1, max_depth)) return true;
                //还原备份
                memcpy(q, w[depth], sizeof q);
            }
        }
    return false;
}
int main() {
    int t; cin >> t;
    while (t --) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> q[i];
        int depth = 0;
        while (depth < 5 && !dfs(0, depth)) depth ++;
        if (depth >= 5) cout << "5 or more" << endl;
        else cout << depth << endl;
    }
    return 0;
}