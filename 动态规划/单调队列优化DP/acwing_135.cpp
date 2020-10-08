/*
* @Description: 135. 最大子序和
* @Author: Xiaobin Ren
* @Date:   2020-10-08 20:17:15
* @Last Modified time: 2020-10-08 20:17:24
*/
#include <iostream>
#include <climits>
using namespace std;
typedef long long ll;

//这题也叫滑动窗口 

const int N = 300010;
int q[N];  //单调队列下标
ll s[N]; //前缀和
int n, m;

//对于单调队列的下标问题：
//如果是从0开始写的代码，那么i就是窗口的最后一个元素 则判断条件是i - q[hh] + 1 > m
//就要hh++ 对于本题 下标从1开始，窗口的结尾元素下标是i - 1, 而i是窗口后的一个元素
//下标好迷啊 我操


int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++ ){
        cin >> s[i];
        s[i] += s[i - 1];
    }
    int hh = 1, tt = 1;  //队头 队尾
    
    ll res = INT_MIN;
    for(int i = 1; i <= n; i++){
        if(i - q[hh]> m) hh++;
        res = max(res, s[i] - s[q[hh]]);
        while(hh <= tt && s[q[tt]] >= s[i]) tt--;
        q[++tt] = i; //队尾下标
    }
    
    cout <<res << endl;
    
    return 0;
}