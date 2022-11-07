#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;

/*
题意为给定一个DFS序（欧拉序）求满足该序列的 不同构 树结构的数量
区间DP/记忆化搜索
此为记忆化搜索写法

https://www.acwing.com/solution/content/10533/
https://www.acwing.com/activity/content/code/content/592398/
https://www.acwing.com/video/1969/  lyd 讲解
*/

/*
reason of why dfs(l+1, k -1) * dfs(k,r) instead of dfs(l + 1, k - 1) * dfs(k, r - 1)
本质上划分其实是把图划分为2部分，一部分为左子树，因为可能是多叉树，所有剩余部分为"另一个子树",
这里其实乘的第二项本质就是包括根节点和除了左子树外其余所有的点组成的序列，而不是不包括根的单纯的多叉树子树
以上述链接题解中的序列为例说明：
A BAB A B A
L     K   R
[l+1,k-1] 为左子树 BAB 序列
剩余ABA为右子树+根节点这部分
*/

/*
为什么这样的阶段划分是有效的：https://www.acwing.com/solution/content/49636/

为了保证计数不重不漏，可以只考虑字串 S[l~r] 的第一棵子树是由哪一段构成的。
枚举划分点 k ，令字串 S[l+1~k-1] 构成 [l,r] 的第一棵子树，如果 k 不相同，
那么字串 S[l+1~k-1] 代表的子树大小也不相同，故不可能产生重复计算。

这里多叉树 A        A  这两种划分来说，第一棵子树的大小是一样的，也就是属于同一个划分集合
          / \      /|\
         B   B    B B B
         2   2    2 1 1
*/

const int N = 310, mod = 1e9;
char s[N];
ll f[N][N];

ll dfs(int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;
    if (f[l][r] != -1) return f[l][r];
    if (s[l] != s[r]) return 0;
    f[l][r] = 0;
    for (int k = l + 2; k <= r; k++) // k += 2 也是可以AC,因为DFS序长度一定为奇数，另一个区间DP解法有说明
        (f[l][r] += dfs(l + 1, k - 1) * dfs(k, r)) %= mod;
    return f[l][r];
}

int main() {
    scanf("%s", s + 1);
    memset(f, -1, sizeof f);
    cout << dfs(1, strlen(s + 1)) << endl;
    return 0;
}