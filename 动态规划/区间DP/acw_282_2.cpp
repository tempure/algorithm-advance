#include <bits/stdc++.h>
using namespace std;


//2022 2.9 update
//区间DP写法
//https://www.acwing.com/video/1971/  lyd讲解

/*
区间DP之所以要先枚举区间长度，是因为计算一个区间时，必须要求所有子问题已经求得答案
对于一个长的区间，在枚举划分时，比当前区间小的长度的所有区间都会计算到，需要先算子问题（具体参考视频讲解）
*/


//f[l][r] 表示合并[l,r]区间的最少代价

const int N = 310;
int f[N][N], s[N]; //s prefix sum

int main() {
    int n;
    cin >> n;
    memset(f, 0x3f, sizeof f);
    for (int i =  1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
        f[i][i] = 0; //单个元素合并代价为0
    }
    for (int len = 2; len <= n; len++)
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            for (int k = 1; k < r; k++)
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
            f[l][r] += s[r] - s[l - 1];
        }
    cout << f[1][n] << endl;
    return 0;
}