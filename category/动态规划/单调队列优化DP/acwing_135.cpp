/*
* @Description: 135. 最大子序和
* @Author: Xiaobin Ren
* @Date:   2020-10-08 20:17:15
* @Last Modified time: 2020-10-08 20:24:31
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
// 此时就要hh++  但是对于这个题，是要求前缀和的 s[r] - s[l-1] 窗口的结尾元素下标
//依旧是i 但是 注意：窗口的开始元素 是q[hh]后边的一个元素 所以才能用s[i]-s[q[hh]] 求出
//相当于窗内一直留了m + 1个元素，第一个不算，只是用来求前缀和的

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