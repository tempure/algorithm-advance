/*
染色法判别二分图
时间复杂度是O(n+m), n 表示点数，m 表示边数
给定一个n个点m条边的无向图，图中可能存在重边和自环。
请你判断这个图是否是二分图。第一行包含两个整数n和m。
接下来m行，每行包含两个整数u和v，表示点u和点v之间存在一条边
*/
/*
一个图是二分图 当且仅当图中没有奇数环 如果没有奇数环 那么反之也一定是二分图
证明直接用奇数环 假设起点属于一个集合 最后导致起点矛盾 QED.
染色过程 只要有一个点颜色确定 整个图的染色就已经确定了
所以总而言之 用2种颜色能染色成功 那就是二分图
*/
const int N = 100010, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int color[N];
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}
//当前点是 u 颜色是c 颜色用 1和2 表示不同的两种颜色
bool dfs(int u, int c) {
    color[u] = c;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!color[j]) { //还没有染色
            dfs(j, 3 - c);  //3 - c将1 变为2， 2变为1
        } else if (color[j] == c) return false; //已经染色 但是 一条边2个顶点颜色一样 染色失败
    }
    return true;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    int a, b;
    while (m--) {
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    bool flag = true;
    for (int i = 1; i <= n; i++) //染色每一个点
        if (!color[i]) {
            if (!dfs(i, 1)) { //染色矛盾
                flag = false;
                break;
            }
        }
    if (flag) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}