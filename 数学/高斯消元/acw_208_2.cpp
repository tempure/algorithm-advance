#include <bits/stdc++.h>
using namespace std;

const int N = 30;
int n, a[N][N];

void solve() {
    memset(a, 0, sizeof a);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i][n + 1];
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        a[i][n + 1] ^= t;
        a[i][i] = 1;
    }
    int x, y;
    while (cin >> x >> y, x || y) a[y][x] = 1;
    auto t = [&]()->int{
        int r, c;
        for (r = 1, c = 1; c <= n; c++) {
            //找主元
            int t = r;
            for (int i = r + 1; i <= n; i++)
                if (a[i][c])
                    t = i;
            if (!a[t][c]) continue; //没有主元
            //将主元所在行交换到最上方
            for (int i = c; i <= n + 1; i++) swap(a[t][i], a[r][i]);
            //消掉
            for (int i = r + 1; i <= n; i++) //将1下边的全部消成0
                if (a[i][c])
                    for (int j = c; j <= n + 1; j++)
                        a[i][j] ^= a[r][j];   //  下边如果是0 那异或1还是0  如果是1  那和1异或之后就是0了
            r++;
        }

        int res = 1;
        if (r < n + 1) {
            for (int i = r; i <= n; i++) {
                if (a[i][n + 1]) return -1;
                res *= 2;
            }
        }
        return res;
    };

    if (t() == -1) puts("Oh,it's impossible~!!");
    else cout << t() << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}