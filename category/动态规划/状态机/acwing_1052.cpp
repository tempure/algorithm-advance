/*
* @Description: 1052. 设计密码
* @Author: Xiaobin Ren
* @Date:   2020-09-29 20:45:09
* @Last Modified time: 2020-09-29 20:45:22
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 55, mod = 1e9 + 7;
int n, m;
int f[N][N];
char str[N];
//kmp + 状态机 复杂度 N * M * 26
int main() {

    cin >> n >> str + 1;
    m = strlen(str + 1); //字串长度

    int ne[N] = {0};
    // kmp 求next数组
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && str[i] != str[j + 1]) j = ne[j];
        if (str[i] == str[j + 1]) j ++;
        ne[i] = j;
    }

    f[0][0] = 1;
    for (int i = 0; i < n; i++) //密码串的当前位置的下标指针 从0开始 字串从1开始
        for (int j = 0; j < m; j++) // 字串进行kmp 和密码串匹配
            for (char k = 'a'; k <= 'z'; k++) { //密码串的该位置 尝试所有字母 进行匹配
                int u = j;
                while (u && k != str[u + 1]) u = ne[u];
                if (k == str[u + 1]) u++; //u会回跳到next位置 或者后移
                //如果回跳 或者后移 但是都没有到短串m的末尾 那么就是符合方案
                //这个时候 更新 回跳到的位置 的状态

                //核心转移方程:
                // f[i + 1][u]表示的是在长度为i + 1的的所有字符串中 使得我们的模式串最终停留在位置u的字符串总数。
                // 而它正是由长度为i的字符串中那些下一次匹配可以转移到u的位置所转移过来的
                if (u < m) f[i + 1][u] = (f[i + 1][u] + f[i][j]) % mod; //u走不到末尾 说明是合法方案
            }

    int res = 0;
    for (int i = 0; i < n; i++) res = (res + f[n][i]) % mod;

    cout << res << endl;

    return 0;
}