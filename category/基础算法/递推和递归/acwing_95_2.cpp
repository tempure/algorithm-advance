#include <iostream>
#include <cstring>
using namespace std;

/*
显然如果第一行的状态已经确定了的话，为了把所有位置都要变成1，那么整个变换的过程就已经确定了
因为我们要通过操作下一行来让当前行的0变成1，而不能操作当前行，因为当前行内操作永远不能全1

对于一个初始给定的状态，直接枚举第一行所有的操作，也就是1<<5种方法操作第一行
用状态k = 1 << 5表示所有状态，如果当前二进制位是1，那么代表turn第一行的当前位置, 0代表不动
然后直接从第二行模拟就行了，如果当前行是0，那么下一行的该纵坐标位置肯定要变化

每次枚举每种第一行的操作方法时，同时对答案取min操作
*/

const int N = 10;
char g[N][N];

int dx[5] = {0, -1, 0, 1, 0}, dy[5] = {0, 0, 1, 0, -1};

void turn(int x, int y) {
    for (int i =  0; i < 5 ; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < 5 && b >= 0 && b < 5) g[a][b] ^= 1;
    }
}

int solve() {
    int ans = 0x3f3f3f3f;
    for (int k = 0; k < 1 << 5; k++) { //第一行的32种状态
        int res = 0;
        char back[10][10];
        memcpy(back, g, sizeof g);
        for (int j = 0; j < 5; j++) {
            if (k >> j & 1) { //按当前位置
                res ++;
                turn(0, j);
            }
        }

        for (int i = 0; i < 4; i++) //剩下的所有行 模拟
            for (int j = 0; j < 5; j++)
                if (g[i][j] == '0') {
                    res ++;
                    turn(i + 1, j);
                }

        bool flag = true;
        for (int j = 0; j < 5; j++) {
            if (g[4][j] == '0') { //最后一行如果有0 说明这种第一行的操作方法不行
                flag = false;
                break;
            }
        }
        if (flag) ans = min(ans, res); //可以的话就更新答案
        memcpy(g, back, sizeof g); //操作完一种第一行的状态情况后，还原题目初始的g[]
    }
    if (ans > 6) ans = -1;
    return ans;

}

int main() {
    int t; cin >> t;
    while (t --) {
        for (int i = 0; i < 5; i++) cin >> g[i];
        cout << solve() << endl;
    }
    return 0;
}