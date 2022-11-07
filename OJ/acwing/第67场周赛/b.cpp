#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//先枚举交换的列
//然后暴力check行

const int N = 22;

int n, m;
int g[N][N];

bool check() {
    for (int i = 0; i < n; i ++ ) {
        int cnt = 0;
        for (int j = 0; j < m; j ++ )
            if (g[i][j] != j + 1)
                cnt ++ ;
        if (cnt > 2) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ )
            cin >> g[i][j];

    for (int i = 0; i < m; i ++ )
        for (int j = i; j < m; j ++ ) {
            for (int k = 0; k < n; k ++ ) swap(g[k][i], g[k][j]);
            if (check()) {
                puts("YES");
                return 0;
            }
            for (int k = 0; k < n; k ++ ) swap(g[k][i], g[k][j]);
        }

    puts("NO");
    return 0;
}