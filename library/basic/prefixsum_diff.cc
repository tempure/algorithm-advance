/*
一维前缀和：
    当a[]数组只初始化一次的时候
    可以直接用a[]读入的时候计算前缀和
    S[i] = a[1] + a[2] + ... a[i]
    a[l] + ... + a[r] = S[r] - S[l - 1]
二维前缀和：
    S[i, j] = 第i行j列格子左上部分所有元素的和
    以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵的和为：
    S[x2, y2]-S[x1-1,y2]-S[x2, y1-1]+S[x1-1, y1-1]
一维差分：
    给区间[l, r]中的每个数加上c：B[l] += c, B[r + 1] -= c
二维差分：
    给以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵中的所有元素加上c：
    S[x1, y1] += c, S[x2 + 1, y1] -= c,
    S[x1, y2 + 1] -= c, S[x2 + 1, y2 + 1] += c
*/
/*
    例题：子矩阵求和
    输入一个n行m列的整数矩阵，再输入q个询问，每个询问包含四个整数x1, y1, x2, y2，
    表示一个子矩阵的左上角坐标和右下角坐标。对于每个询问输出子矩阵中所有数的和。
*/
int n, m, q;
const int N = 1010;
int s[N][N], a[N][N];
int main() {
    scanf("%d%d%d" , &n, &m, &q);
    //前缀和问题下标都从1开始处理
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
    while (q--) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        printf("%d\n", s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1]);
    }
    return 0;
}
/*
    例题:一维差分
    输入一个长度为n的整数序列。
    接下来输入m个操作，每个操作包含三个整数l, r, c，表示将序列中[l, r]之间的每个数加上c。
    请你输出进行完所有操作后的序列。
*/
const int N = 100010;
int a[N], b[N];
int n , m;
void insert(int l, int r, int c) {
    b[l] += c;
    b[r + 1] -= c;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        insert(i, i, a[i]); //构造差分序列
    }
    while (m--) {
        int l, r, c;
        cin >> l >> r >> c;
        insert(l, r, c);
    }
    //所有操作结束后 求前缀和 就是最终的修改结果
    for (int i = 1; i <= n; i++) b[i] += b[i - 1];
    for (int i = 1; i <= n; i++) cout << b[i] << ' ';
    cout << endl;
    return 0;
}

/*
    例题：二维差分
    输入一个n行m列的整数矩阵，再输入q个操作，每个操作包含五个整数x1, y1, x2, y2, c，
    其中(x1, y1)和(x2, y2)表示一个子矩阵的左上角坐标和右下角坐标。
    每个操作都要将选中的子矩阵中的每个元素的值加上c。
    请你将进行完所有操作后的矩阵输出。
*/
const int N = 1010;
int a[N][N], b[N][N];
int n, m, q;
//差分的核心，输入时候初始化可直接使用insert()
void insert(int x1, int y1, int x2, int y2, int c) {
    b[x1][y1] += c;
    b[x2 + 1][y1] -= c;
    b[x1][y2 + 1] -= c;
    b[x2 + 1][y2 + 1] += c;

}
int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            insert(i, j, i, j, a[i][j]);
    while (q--) {
        int x1, y1, x2, y2, c;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
        insert(x1, y1, x2, y2, c);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1]; //差分完求一次二维前缀和就是修改后的数组了
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (j == m) printf("%d\n", b[i][j]);
            else printf("%d ", b[i][j]);
    return 0;
}