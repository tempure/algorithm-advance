//矩阵乘法模板
const int N = 3;
void mul(int c[], int a[], int b[][N]) {//c=a*b一维乘二维
    int temp[N] = {0};
    for (int i = 0; i < N; i++) //列
        for (int j = 0; j < N; j++) //行
            temp[i] = (temp[i] + (ll)a[j] * b[j][i]); //这里可选是否取模
    memcpy(c, temp, sizeof temp); //这里要写temp  因为传进来的c只是一个指针
}
//对于一行的矩阵*二维的矩阵
//可以将一行的矩阵初始化为二维的，除了第一行其余 行为0即可
void mul(int c[][N], int a[][N], int b[][N]) { //c = a * b //二维相乘
    int temp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                temp[i][j] = (temp[i][j] + (ll)a[i][k] * b[k][j]);//此处可选取模 % m;
    memcpy(c, temp, sizeof temp);
}
/*
例题：f1=1,f2=1,f3=2,f4=3,…,fn=fn−1+fn−2。
输入n和m，求fn的前n项和
*/
//矩阵乘法复杂度O(N ^ 3 * log N)
//构造3x3矩阵来递推 [f[n], f[n + 1], s[n]] -> [f[n + 1], f[n + 2],  s[n + 1]]
//[0, 1, 0]
//[1, 1, 1]
//[0, 0, 1]
const int N = 3;
int n, m;
void mul(int c[], int a[], int b[][N]) { //c = a  * b
    int temp[3] = {0};
    for (int i = 0; i < N; i++) //列
        for (int j = 0; j < N; j++) //行
            temp[i] = (temp[i] + (ll)a[j] * b[j][i]) % m;
    memcpy(c, temp, sizeof temp); //这里要写temp  因为传进来的c只是一个指针
}
void mul(int c[][N], int a[][N], int b[][N]) { //c = a * b //二维相乘
    int temp[N][N] = {0};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                temp[i][j] = (temp[i][j] + (ll)a[i][k] * b[k][j]) % m;
    memcpy(c, temp, sizeof temp);
}
int main() {
    cin >> n >> m;
    int f1[3] = {1, 1, 1}; //初始状态 [f[1], f[2], s[1]]
    int a[3][3] = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 1}
    };
    n -- ; //从1开始 递推n - 1 次
    while (n) {
        if (n & 1) mul(f1, f1, a); //res = res * a
        mul(a, a, a); // a = a * a
        n >>= 1;
    }
    //最后递推之后的f1就是 [f[n], f[n + 1], s[n]]
    cout << f1[2] << endl;
    return 0;
}