//时间复杂度是 O(n^3), n 表示点数
//图中要求不存在负权回路
const int  N = 210, INF = 1e9;
int n, m , k;
int d[N][N];
void floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
    int a , b , x;
    while (m --) {
        cin >> a >> b >> x;
        d[a][b] = min(d[a][b], x); //判断重边
    }
    floyd();
    while (k--) {
        cin >> a >> b;
        if (d[a][b] > INF / 2)  cout << "impossible" << endl; //即使没有路径 也可能会把无穷给更新 不能判断==INF
        else cout << d[a][b] << endl;
    }
    return 0;
}
/*
传递闭包
给定 n 个变量和 m 个不等式。其中 n 小于等于26，变量分别用前 n 的大写英文字母表示。
不等式之间具有传递性，即若 A>B 且 B>C ，则 A>C。
请从前往后遍历每对关系，每次遍历时判断：
如果能够确定全部关系且无矛盾，则结束循环，输出确定的次序；
如果发生矛盾，则结束循环，输出有矛盾；
如果循环结束时没有发生上述两种情况，则输出无定解。
输入格式
输入包含多组测试数据。
每组测试数据，第一行包含两个整数n和m。
接下来m行，每行包含一个不等式，不等式全部为小于关系。
当输入一行0 0时，表示输入终止。
数据范围
2 <= n <= 26，变量只可能为大写字母A~Z。
*/
//提前break题意：如果前i个已经推出所有关系 即使第i + 1 个矛盾 也当作成立
//矛盾判断：d[i][i] == 1 因为A > B, B > A ->  A > A
//唯一确定：d[i][j], d[j][i] 必有一个是1 一个是0
//不能确定：d[i][j] == 0 && d[j][i] == 0
//排序：一个没有被其他数标记过的数 就是最小数
const int N = 26;
int n, m ;
bool g[N][N], d[N][N];
bool st[N];
void floyd() {
    memcpy(d, g, sizeof d);

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] |= d[i][k] && d[k][j];
}
int check() {
    for (int i = 0; i < n; i++)
        if (d[i][i]) return 2;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++) //这里是枚举点对 i,j 所以j不是1到n
            //如果运行到这里 说明所有d[i][i]都是0如果i==j
            //只要遇到一个d[i][i]就直接返回0了 不会再判断其他点对了所以这个判断的前提是i!=j
            //或者 j如果循环到n 那么可以写为 if(!d[i][j] && !d[j][i] && i != j)
            if (!d[i][j] && !d[j][i]) //都是0  也就是不能确定
                return 0;
    return 1; //唯一确定
}
char get_min() {
    for (int i = 0; i < n; i++)
        if (!st[i]) {
            bool flag = true;
            for (int j = 0; j < n; j++) //找有没有比i小的 并且没有标记的 这里找到的一定是最小的 因为i是从0开始枚举的
                if (!st[j] && d[j][i]) {
                    flag = false;
                    break;
                }
            if (flag) {
                st[i] = true;
                return 'A' + i;
            }
        }
}
int main() {
    while (cin >> n >> m , n || m) {
        memset(g, 0, sizeof g);
        int type = 0, t;  //type 0不能确定1唯一2矛盾 t轮数
        for (int i = 1; i <= m; i++) { //迭代m次 就是m个不等式关系
            char str[5];
            cin >> str;
            int a = str[0] - 'A', b = str[2] - 'A';
            if (!type) { //当所有状态都确定就不会进入这个判断
                //floyd 每加一个大小关系就判断一下
                //目的就是最早break 由题意
                g[a][b] = 1;
                floyd();
                type = check();
                if (type) t = i;
            }
        }
        if (!type) puts("Sorted sequence cannot be determined.");
        else if (type == 2) printf("Inconsistency found after %d relations.\n", t);
        else { //唯一确定
            memset(st, 0, sizeof st);
            printf("Sorted sequence determined after %d relations: ", t);
            for (int i = 0; i < n; i++) printf("%c", get_min());
            printf(".\n");
        }
    }
    return 0;
}