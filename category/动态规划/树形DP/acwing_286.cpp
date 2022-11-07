#include <bits/stdc++.h>
using namespace std;

//分组背包+树形DP 多叉树
//https://www.acwing.com/activity/content/code/content/592402/
//https://www.acwing.com/video/1967/

const int N = 310;
vector<int> son[N];
int f[N][N], s[N], n, m; //f[s][t] 子树s共选了t门课 最大学分

/*
由于题目给出的不一定是连通图，也就是可能为森林
加入虚拟根节点，为所有课程的先修课，学分为0，转换为共选M+1门课
*/

void dp(int x) {
    f[x][0] = 0;
    for (int i = 0; i < son[x].size(); i++) { // x为根的每棵子树 也就是每个分组
        int y = son[x][i]; //每棵子树y就是一个分组
        dp(y);
        for (int t = m; t >= 0; t --) // 倒序循环当前选课总门数（当前背包体积）
            for (int j = 0; j <= t; j++) // 循环x更深子树y上的选课门数（组内物品）
                f[x][t] = max(f[x][t], f[x][t - j] + f[y][j]); //子树y选课j门
    }
    if (x != 0) // x不为0时，选修x本身需要占用1门课，并获得相应学分
        // 这里直接就用t-1把t的情况覆盖掉了，所以上面for循环j到t其实无所谓，最后这个值直接就扔掉了
        for (int t = m; t > 0; t --)
            f[x][t] = f[x][t - 1] + s[x];
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x >> s[i]; //s[]学分
        son[x].push_back(i);
    }
    memset(f, 0xcf, sizeof f);
    dp(0);
    cout << f[0][m] << endl;
    return 0;
}