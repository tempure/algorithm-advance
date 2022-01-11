#include <bits/stdc++.h>
using namespace std;

//POJ 2279
//https://www.acwing.com/solution/content/4954/
//https://www.acwing.com/video/397/

typedef long long LL;

const int N = 31;

int n;
LL f[N][N][N][N][N];

void solve() {
    while (cin >> n, n) {
        int s[5] = {0};
        for (int i = 0; i < n; i ++ ) cin >> s[i];
        memset(f, 0, sizeof f);
        f[0][0][0][0][0] = 1;

        for (int a = 0; a <= s[0]; a ++ )
            for (int b = 0; b <= min(a, s[1]); b ++ )
                for (int c = 0; c <= min(b, s[2]); c ++ )
                    for (int d = 0; d <= min(c, s[3]); d ++ )
                        for (int e = 0; e <= min(d, s[4]); e ++ ) {
                            LL &x = f[a][b][c][d][e];
                            if (a && a - 1 >= b) x += f[a - 1][b][c][d][e];
                            if (b && b - 1 >= c) x += f[a][b - 1][c][d][e];
                            if (c && c - 1 >= d) x += f[a][b][c - 1][d][e];
                            if (d && d - 1 >= e) x += f[a][b][c][d - 1][e];
                            if (e) x += f[a][b][c][d][e - 1];
                        }
        cout << f[s[0]][s[1]][s[2]][s[3]][s[4]] << endl;
    }
}

int main() {
    solve();
    return 0;
}