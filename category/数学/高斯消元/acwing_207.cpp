#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

const int N = 15;
const double eps = 1e-6;
double a[N][N];
double b[N][N];
int n;
void gauss() {
    int c, r;  //列和行
    for (c = 1, r = 1; c <= n; c++, r++) { //列向右移动 因为要变成上三角矩阵 注意：该矩阵是 n * (n + 1) 的
        int t = r;
        for (int i = r; i <= n; i++) //求出绝对值最大的行
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
        if (fabs(a[t][c]) < eps) continue; //绝对值最大也是0 说明这一列全0 直接下一列c++即可
        for (int i = c; i <= n + 1; i++) swap(a[t][i], a[r][i]); //把这行换到最上面(第r行)也就是是固定行的下一行
        for (int i = n + 1; i >= c; i--) a[r][i] /= a[r][c]; //第一个数变成1 后边的同时改变
        for (int i = r + 1; i <= n; i++) //把第一个数下面该列的元素 都消成0 行下标是 0 ~ n-1
            if (fabs(a[i][c]) > eps) // 这一行该列元素不是0 才需消掉
                for (int j = n + 1; j >= c; j--)
                    a[i][j] -= a[r][j] * a[i][c]; //被消去的元素减去 第r行元素 * 该行第一个元素，因为r行第一个是1
    }

    //有唯一解 将增广矩阵化为简化阶梯矩阵 每行最后一个元素就是唯一解了
    //这里就是把每行 元素 1 后边的非0元素全部改为0  每行的1将该1所在列上方元素全部消成0
    //但是事实上并没有消 只对于每行的最后一个元素在模拟这个过程 输出最后的矩阵 不是简化阶梯矩阵
    for (int i = n; i > 1; i -- )
        for (int j = i - 1; j; j-- ) {
            a[j][n + 1] -= a[i][n + 1] * a[j][i];
            a[j][i] = 0;
        }
}

int main() {
    cin >> n;
    for (int i = 0; i < n + 1; i++)
        for (int j = 1; j <= n; j++) //每行n + 1 个元素
            cin >> b[i][j];

    //每一行都就减去第一行
    for (int i = 1; i <= n; i++)  //从第二行开始
        for (int j = 1; j <= n; j++) {
            a[i][j] += 2 * (b[i][j] - b[0][j]);
            a[i][n + 1] += b[i][j] * b[i][j] - b[0][j] * b[0][j];
        }

    gauss();

    for (int i = 1; i <= n; i++) printf("%.3lf ", a[i][n + 1]); //最后矩阵系数都是1 最后列常数列就是解
    return 0;
}