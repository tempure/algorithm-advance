#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
核心思想: 只考虑横放的所有情况，然后判断剩下的位置能否被竖着放的填满
f[][]也只表示了横放的情况，f[0][0]就是所有都被竖着的填满

f[i][j]: 前i-1列已经摆好，且第i-1列伸出到第i列的状态是j的所有方案数
f[i-1][k] -> f[i][j] 转移，表示i-1列伸出到第i列后状态依然合法，然后加上方案数即可
*/

const int N = 12, M = 1 << N;

int n, m;
ll f[N][M];
vector<int> state[M];
bool st[M];

int main() {
    while (cin >> n >> m, n || m) {
        for (int i = 0; i < 1 << n; i++) { //每一列用n位二进制能组成的所有状态的合法性，也就是竖着连续的1的个数的奇偶性
            int cnt = 0;
            bool is_valid = true; //0表示当前列的该位置没有被之前的一列插进来，是空的，1代表已经被占用
            for (int j = 0; j < n; j++) //状态i的所有连续0段, 0的个数，是否是偶数
                if (i >> j & 1) { //遇到一个1，之前的cnt是否是偶数
                    if (cnt & 1) {
                        is_valid = false;
                        break;
                    }
                    cnt = 0;
                }
                else cnt ++;
            if (cnt & 1) is_valid = false; //最后一段状态，也就是最下面的连续0段是否合法
            st[i] = is_valid;
        }

        for (int i = 0; i < 1 << n; i++) { //枚举所有的列的二进制状态对，理解为第i列向后面一列伸出，此时的局面，预处理可达每个状态的所有合法状态
            state[i].clear(); //多测试样例 ，vector 要清空
            for (int j = 0; j < 1 << n; j++)
                if ((i & j) == 0 && st[i | j]) //i&j==0该列的同一行不能有交集放置, i|j是所有是1的位置被填，剩余0此时的状态依然合法
                    state[i].push_back(j);
        }

        memset(f, 0, sizeof f);
        f[0][0] = 1; //只放竖着的
        for (int i = 1; i <= m; i++) //枚举所有的列来尝试填补残局
            for (int j = 0; j < 1 << n; j++) // 枚举所有列的状态
                for (auto k : state[j]) //每个能到状态j的合法状态,也就是第i列加上i-1列的某些状态，这些状态从i-1伸出到i列后当前局面依然合法。 已经在上面与处理过了。
                    f[i][j] += f[i - 1][k];

        cout << f[m][0] << endl; //最后一列，且所有位置都被填满的总方案数
    }
    return 0;
}