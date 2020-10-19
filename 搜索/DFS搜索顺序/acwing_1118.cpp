/*
* @Description: 1118. 分成互质组
* @Author: Xiaobin Ren
* @Date:   2020-10-19 12:10:27
* @Last Modified time: 2020-10-19 12:10:41
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//将某个数加到最后一组
//或者重开一个新的组

const int N = 15;
int p[N];
int group[N][N];
bool st[N];
int ans = N; //初始答案 最大值是N
int n;

int gcd(int a, int b){
    return b ? gcd(b, a % b) : a;
}

bool check(int group[], int gc, int i){
    for(int j = 0; j < gc; j++)
        if(gcd(p[group[j]], p[i]) > 1)
            return false;
    return true;
}

//第几组 当前组内的元素下标 搜索的元素总数 该组开始搜索的元素下标
void dfs(int g, int gc, int tc, int start){
    if(g >= ans) return ; //不是最优解 剪枝
    if(tc == n) ans = g;
    
    bool flag = true;  //当前组内是否可以添加某些元素
    
    for(int i = start; i < n; i++){
        //没搜过 并且当前组内所有元素和i都互质 group[]存的是下标
        if(!st[i] && check(group[g], gc, i)){
            st[i] = true;
            group[g][gc] = i;
            dfs(g, gc + 1, tc + 1, i +1);
            st[i] = false; //恢复现场
            
            flag = false;
        }
    }
    //只能重新开一组
    if(flag ) dfs(g + 1, 0, tc, 0);
}


int main(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> p[i];
    
    dfs(1, 0, 0, 0); //第一组开始 组内0个元素 当前一共搜了0个元素 该组从0号元素开始搜
    cout << ans << endl;
    return 0;
}