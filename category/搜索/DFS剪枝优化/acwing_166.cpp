/*
* @Description: 166. 数独
* @Author: Xiaobin Ren
* @Date:   2020-10-20 20:39:33
* @Last Modified time: 2020-10-20 20:39:45
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

const int N = 9;
int row[N], col[N], cell[3][3];
char str[100]; // 以char存储  总81个
int ones[1 << N];  //打表查二进制位数
int map[1 << N]; //打表lowbit的处理结果 直接返回二进制位 而不是二进制表示的数字



int lowbit(int x){
    return x & -x;
}

void init(){
    //二进制位是1表示可以填 是0表示不能填 初始时所有位置都可以填 所以都是1 也就是 (1 << N) - 1
    for(int i = 0; i < N; i++) row[i] = col[i] = (1 << N) - 1;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        cell[i][j] = (1 << N) - 1; // 每个3 x 3 格子 用一个9位二进制数表示状态
}

inline int get(int x, int y){ //非递归函数加inline才有用 
    return row[x] & col[y] & cell[x / 3][y / 3];
}

bool dfs(int cnt){
    if(cnt == 0) return true;
    //找出可选方案最少的格子
    int minv = INT_MAX;
    int x, y;  //坐标
    for(int i  = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(str[i * 9 + j] == '.'){
                int t = ones[get(i, j)]; //可选的个数
                if(t < minv){
                    minv = t;
                    x = i, y = j;
                }
            }
        //循环之后 x,y就是分支最少的下标 最优搜索 剪枝
    for(int i = get(x, y); i ;i -= lowbit(i)){  //当前的x y 已经是选定要放数字的格子
        int t = map[lowbit(i)]; //映射到编号
        
        //修改状态
        row[x] -= 1 << t;
        col[y] -= 1 << t;
        cell[x/3][y/3] -= 1 << t;
        str[x * 9 + y] = '1' + t;
        
        if(dfs(cnt - 1)) return true;
        
        //恢复现场
        row[x] += 1 << t;
        col[y] += 1 << t;
        cell[x/3][y/3] += 1 << t;
        str[x * 9 + y] = '.';
    }
    
    return false;
}



int main(){
    for(int i = 0; i < N; i++) map[1 << i] = i;
    for(int i = 0; i < 1 << N; i++){ //打表
        int  s = 0;
        for(int j = i; j; j -= lowbit(j) ) s++;
        ones[i]  = s;//i的二进制表示有s个1
    }
    
    while(cin >> str, str[0] != 'e'){
        init();
        int cnt = 0;
        for(int i = 0, k = 0; i < N; i++)  // i j 为横纵坐标 k为 样例的遍历下标
            for(int j = 0; j < N; j++, k++)
                if(str[k] != '.'){
                    int  t = str[k] - '1';  //将1到9的下标改为 0到8
                    row[i] -= 1 << t;
                    col[j] -= 1 << t;
                    cell[i/3][j/3] -= 1 << t;
                }else cnt ++; //cnt 记录要填格子的个数
       dfs(cnt);
       cout << str << endl;
    }
    
    return 0;
}

