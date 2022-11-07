/*复杂度O(n^3)
a11*x1 + a12*x2 + ... + a1n*xn = b1
a21*x1 + a22*x2 + ... + a2n*xn = b2
... .... ... ..
am1*x1 + am2*x2 + ... + amn*xn = bm
第一行包含整数n。
接下来n行，每行包含n+1个实数，表示一个方程的n个系数以及等号右侧的常数。
如果给定线性方程组存在唯一解，则输出共n行，其中第i行输出第i个未知数的解，结果保留两位小数。
如果给定线性方程组存在无数解，则输出“Infinite group solutions”。
如果给定线性方程组无解，则输出“No solution”。
*/
const int N = 110;
const double eps = 1e-6;
double a[N][N];
int n;
int gauss() {
    int c, r;  //列和行
    for (c = 0, r = 0; c < n; c++) { //列向右移动 因为要变成上三角矩阵 注意：该矩阵是 n * (n + 1) 的
        int t = r;
        for (int i = r; i < n; i++) //求出绝对值最大的行
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
        if (fabs(a[t][c]) < eps) continue; //绝对值最大也是0 说明这一列全0 直接下一列c++即可
        for (int i = c; i <= n; i++) swap(a[t][i], a[r][i]); //把这行换到最上面(第r行)也就是是固定行的下一行
        for (int i = n; i >= c; i--) a[r][i] /= a[r][c]; //第一个数变成1 后边的同时改变
        for (int i = r + 1; i < n; i++) //把第一个数下面该列的元素 都消成0 行下标是 0 ~ n-1
            if (fabs(a[i][c]) > eps) // 这一行该列元素不是0 才需消掉
                for (int j = n; j >= c; j--)
                    a[i][j] -= a[r][j] * a[i][c]; //被消去的元素减去 第r行元素 * 该行第一个元素，因为r行第一个是1
        r ++;
    }
    if (r < n) { //不是有唯一解
        for (int i = r; i < n; i++)
            if (fabs(a[i][n]) > eps) //0==非0
                return 2;  //无解
        return 1;//无穷多解
    }
    //有唯一解 将增广矩阵化为简化阶梯矩阵 每行最后一个元素就是唯一解了
    //这里就是把每行 元素 1 后边的非0元素全部改为0  每行的1将该1所在列上方元素全部消成0
    //但是事实上并没有消 只对于每行的最后一个元素在模拟这个过程 输出最后的矩阵 不是简化阶梯矩阵
    for (int i = n - 1; i >= 0; i -- )
        for (int j = i + 1; j < n; j ++ )
            a[i][n] -= a[i][j] * a[j][n];
    return 0;  // 唯一解
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n + 1; j++) //每行n + 1 个元素
            cin >> a[i][j];
    int t = gauss();
    if (t == 0) {
        for (int i = 0; i < n; i++) printf("%.2f\n", a[i][n]); //最后矩阵系数都是1 最后列常数列就是解
    } else if (t == 1) puts("Infinite group solutions"); //无数解
    else puts("No solution");  //无解
    return 0;
}
/*
异或线性方程组 O(n^3)
M[1][1]x[1] ^ M[1][2]x[2] ^ … ^ M[1][n]x[n] = B[1]
M[2][1]x[1] ^ M[2][2]x[2] ^ … ^ M[2][n]x[n] = B[2]
…
M[n][1]x[1] ^ M[n][2]x[2] ^ … ^ M[n][n]x[n] = B[n]
第一行包含整数n。
接下来n行，每行包含n+1个整数0或1，表示一个方程的n个系数以及等号右侧的常数。
*/
const int N  = 110;
int a[N][N]; int n;
int gauss() {
    int r, c;
    for (r = c = 0; c < n; c++) { //外层枚举列
        int t = r;
        for (int i = r; i < n; i++)
            if (a[i][c]) {
                t = i;
                break;  //找到一个非0行即可
            }
        if (!a[t][c]) continue;  //该列全部都是0 直接下一列
        //该行交换上去 最上面 未固定的
        for (int i = c; i <= n; i++) swap(a[t][i], a[r][i]); //从左往右扫 交换2行的每一个元素
        for (int i = r + 1; i < n; i++) //将1下边的全部消成0
            if (a[i][c])
                for (int j = c; j <= n; j++)
                    a[i][j] ^= a[r][j];   //  下边如果是0 那异或1还是0  如果是1  那和1异或之后就是0了
        r++;
    }
    if (r < n) {
        for (int i = r; i < n; i++) //此时的r所在的行 就是只有一个未知数的方程 开始判断0 = 非0
            if (a[i][n]) return 2; //无解
        return 1;  //无数解
    }
    //用每一行的主元 消去该列的上边的数 全部为0
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            a[i][n] ^= a[i][j] & a[j][n];
    return 0;  //唯一解
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0 ; j < n + 1; j++)
            cin >> a[i][j];
    int res = gauss();
    if (res == 0) { //唯一解
        for (int i = 0; i < n; i++) cout << a[i][n] << endl;
    } else if (res == 1) { //无数解
        cout << "Multiple sets of solutions" << endl;
    } else cout << "No solution" << endl;
    return 0;
}