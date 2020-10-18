/*
* @Description: 1117. 单词接龙
* @Author: Xiaobin Ren
* @Date:   2020-10-18 23:54:18
* @Last Modified time: 2020-10-18 23:54:40
*/
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 21;

string word[N];
int n;
bool st[N];
int g[N][N];  //两个单词 重合的部分 后缀和前缀 重合的最小值
int used[N];  //使用的次数 每个单词
int ans; //答案 最长

void dfs(string dragon, int last){  //上一个单词的编号
    ans = max((int)dragon.size() ,ans);
    
    used[last] ++;
    
    for(int i = 0; i < n; i++)
        if(g[last][i] && used[i] < 2)
        //  last的后缀和i的前缀重合的部分 就不用再加了
            dfs(dragon + word[i].substr(g[last][i]),i);
    
    used[last] --; //恢复现场
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> word[i];
    char start;
    
    cin >> start;
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            string a = word[i], b = word[j];
            for(int k = 1; k < min(a.size(), b.size()); k++)
                if(a.substr(a.size() - k, k) == b.substr(0, k)){
                    //a串的后缀和b串的前缀重合的最小长度
                    g[i][j] = k;
                    break;
                }
        }
        
    for(int i = 0; i < n; i++)
        if(word[i][0] == start)
            dfs(word[i], i); //找到一个以开头字母开头的单词 开始搜 记录一下当前最后一个单词的下标
    
    cout << ans << endl;
    
    return 0;
}