/*
* @Description: 181. 回转游戏
* @Author: Xiaobin Ren
* @Date:   2020-10-22 12:34:02
* @Last Modified time: 2020-10-22 12:34:17
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//估价函数：统计当前8个格子里面最多的一个数 估计函数就是8 - cnt 操作
//2个相反的操作，不能连着出现，不然就是没作用，拍除冗余操作
//打表预处理变换之后的序列

/*
      0     1
      2     3
4  5  6  7  8  9  10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/

const int N = 24;

int q[N];
int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}
};
int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};
int opposite[8] = {5, 4, 7, 6, 1, 0, 3, 2};

int path[100];

int f()
{
    //因为只有123三个数字 所以sum开4就可以
    static int sum[4];
    memset(sum, 0, sizeof sum);
    for (int i = 0; i < 8; i ++ ) sum[q[center[i]]] ++ ;

    int s = 0;
    for (int i = 1; i <= 3; i ++ ) s = max(s, sum[i]);
    return 8 - s;
}

bool check()
{   //检测中间8个数字是否一样 
    for (int i = 1; i < 8; i ++ )
        if (q[center[i]] != q[center[0]])
            return false;
    return true;
}

void operation(int x)
{
    int t = q[op[x][0]];
    for (int i = 0; i < 6; i ++ ) q[op[x][i]] = q[op[x][i + 1]];
    q[op[x][6]] = t;
}

bool dfs(int depth, int max_depth, int last) //最后一个参数记录上一次操作是什么
{
    if (depth + f() > max_depth) return false;
    if (check()) return true;

    for (int i = 0; i < 8; i ++ )
    {
        if (opposite[i] == last) continue; //和上一次操作相反，相当于没操作
        operation(i);
        path[depth] = i;
        if (dfs(depth + 1, max_depth, i)) return true;
        //恢复现场 就是反向操作一次
        operation(opposite[i]);
    }

    return false;
}

int main()
{
    while (scanf("%d", &q[0]), q[0])
    {
        for (int i = 1; i < N; i ++ ) scanf("%d", &q[i]);
        int depth = 0;
        while (!dfs(0, depth, -1))
        {
            depth ++ ;
        }
        if (!depth) printf("No moves needed");
        for (int i = 0; i < depth; i ++ ) printf("%c", 'A' + path[i]);
        printf("\n%d\n", q[6]); //6号位置是左上角的，输入任意一个就行
    }

    return 0;
}