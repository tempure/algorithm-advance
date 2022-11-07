/*
* @Description: 479. 加分二叉树
* @Author: Xiaobin Ren
* @Date:   2020-10-02 11:28:09
* @Last Modified time: 2020-10-02 11:28:33
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//子树的中序遍历 序列一定是连续的一段 因为递归到子树 遍历完之后 才会回到根节点
//字典序最下的答案 就是根节点最靠左的答案 因为是前序遍历 且中序遍历是字典序

//f[l][r] 为中序遍历的序列区间[l,r]的最优值 用g[l][r] 数组来存每个区间的根节点 

const int N = 30;

int n, w[N], f[N][N], g[N][N];

void dfs(int l, int r){  //前序遍历
    if(l > r) return ;
    int root = g[l][r];
    cout << root << ' ';
    dfs(l, root - 1);
    dfs(root + 1,r );
}

int main(){
    
    cin >> n;
    for(int i =1 ; i<= n; i++) cin >> w[i];
    
    for(int len = 1; len <= n; len ++)
        for(int l = 1; l + len -1 <= n; l++){
            int r = l + len - 1;
            if(len == 1){
                f[l][r] = w[l]; //长度为1 那么就是叶节点本身的分支
                g[l][r] = l;
            }
            else{ //不是叶节点的情况  枚举分割位置k 也就是根的位置
                for(int k = l; k<= r; k++){
                    int left = k == l ? 1 : f[l][k - 1]; //左端点 左子树为空为1 
                    int right = k == r ? 1 : f[k + 1][r]; 
                    int score = left * right + w[k];
                    if(f[l][r] < score){ //更新答案
                        f[l][r] = score;
                        g[l][r] = k;
                    }
                }
            }
        }
    
    cout << f[1][n] << endl;
    
    dfs(1,n);
     
    return 0;
}