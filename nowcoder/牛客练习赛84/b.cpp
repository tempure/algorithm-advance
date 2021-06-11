#include <iostream>
#include <cstring>
using namespace std;

const int N = 10;
char g[N][N];

int dx[5] = {0, -1, 0, 1, 0}, dy[5] = {0, 0, 1, 0, -1};

void turn(int x, int y) {
    for (int i =  0; i < 5 ; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < 4 && b >= 0 && b < 4) g[a][b] ^= 1;
    }
}

void solve() {
    bool flag = true;
    for (int k = 0; k < 1 << 4; k++) { //第一行的32种状态
        int res = 0;
        char back[10][10];
        memcpy(back, g, sizeof g);
        for (int j = 0; j < 4; j++) {
            if (k >> j & 1) { //按当前位置
                res ++;
                turn(0, j);
            }
        }

        for (int i = 0; i < 3; i++) //剩下的所有行 模拟
            for (int j = 0; j < 4; j++)
                if (g[i][j] == '1') {
                    res ++;
                    turn(i + 1, j);
                }

        for (int j = 0; j < 4; j++) {
            if (g[3][j] == '1') { //最后一行如果有0 说明这种第一行的操作方法不行
                flag = false;
                break;
            }
        }
        memcpy(g, back, sizeof g); //操作完一种第一行的状态情况后，还原题目初始的g[]
    }
    if (flag) cout << "YES" << endl;
    else cout << "NO" << endl;

}

int main() {
    // int t; cin >> t;
    // int t = 1;
    // while (t --) {
    for (int i = 0; i < 4; i++) cin >> g[i];
    // cout << solve() << endl;
    solve();
    // }
    return 0;
}