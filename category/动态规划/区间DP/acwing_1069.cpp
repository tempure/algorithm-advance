/*
* @Description: 1069. 凸多边形的划分
* @Author: Xiaobin Ren
* @Date:   2020-10-01 20:43:36
* @Last Modified time: 2020-10-01 20:43:50
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = 55, M = 35; //乘积的结果 不会超过30位 三个1e9相乘
int n;
const int INF = 0x3f3f3f3f;
int w[N];
ll f[N][N][M];  //偷懒写法 M长度的向量 不开vector 高精度的数组实现

//1e9的数据相乘 要写高精度
//将整个多边形分成三部分 左右2个多边形 中间一个三角形
//转移方程：f[l][r] = f[l][k] + f[k][r] + w[l] * w[k] * w[r]; //l k r 都是多边形的点权值
//注意 这个不是环形的区间DP 因为只需要遍历一次 多边形的边 然后划分 从任何一个点开始都可以
//和点的遍历顺序是无关的 但是 环形DP与边的遍历顺序是有关的


void add(ll a[], ll b[]){
    static ll c[M];
    memset(c, 0, sizeof c);
    
    for(int i = 0,t = 0; i< M; i++){
        t += a[i] + b[i];
        c[i] = t % 10;
        t /= 10;
    }
    
    memcpy(a, c, sizeof c);  
}

void mul(ll a[] , ll b){
    static ll c[M];
    memset(c, 0, sizeof c);
    
    ll t = 0;
    for(int i = 0; i < M; i++){
        t += a[i] * b;
        c[i] = t % 10;
        t /= 10;
    }
    
    memcpy(a, c, sizeof c);
}

int cmp(ll a[], ll b[]){
    for(int i = M - 1; i >= 0; i--) //从后往前比较
        if(a[i] > b[i]) return 1;
        else if(a[i] < b[i]) return -1;
    
    return 0;
}

void print(ll a[]){
    int k = M - 1; //去除前导0 然后逆着输出
    while(k && !a[k]) k --;
    while(k >= 0) cout << a[k --];
    cout << endl;
}

int main(){
         
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> w[i];
    
    ll temp[M];
    
    for(int len = 3; len <= n; len++)  //长度3开始 2开始构不成三角形
        for(int l = 1; l + len - 1 <= n; l++){ //左端点
            int r = l + len - 1; //右端点
            f[l][r][M - 1] = 1;  //一个1 然后其余都是0 无穷大
            for(int k = l; k < r; k++){//分界线 k从l循环到r - 1
                memset(temp, 0, sizeof temp);
                temp[0] = w[l];
                mul(temp, w[k]);
                mul(temp, w[r]);
                add(temp, f[l][k]);
                add(temp, f[k][r]);
                
                if(cmp(f[l][r], temp) > 0) 
                    memcpy(f[l][r], temp, sizeof temp);
              //  f[l][r] = min(f[l][r], f[l][k] + f[k][r] + w[l] * w[k] * w[r]);
            }
        }
        
    print(f[1][n]);
    
    
    return 0;
}
