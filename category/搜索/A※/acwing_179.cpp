/*
* @Description: 179. 八数码
* @Author: Xiaobin Ren
* @Date:   2020-10-16 23:29:08
* @Last Modified time: 2020-10-16 23:29:31
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <unordered_map>
#include <cmath>
#include <queue>
using namespace std;
typedef pair<int ,string> pis;
#define um unordered_map
#define x first
#define y second

//八数码有解充要条件：序列逆序对数量是偶数
//估价函数:当前数字的位置，和最终位置应该归属的位置的曼哈顿距离

int f(string state){
    int res = 0;
    for(int i = 0 ; i < state.size(); i++)
        if(state[i] != 'x'){
            int t = state[i] - '1';
            res += abs(i / 3 - t / 3) + abs(i % 3  - t % 3);  //曼哈顿距离
        }
    return res;
}

string bfs(string start){
    
    string end = "12345678x";
    
    char op[] = "urdl"; //上右下左 顺时针
    
    um<string, int> dist; //方案和距离
    um<string, pair<char, string> > prev;  //前驱转移路径 
    priority_queue<pis, vector<pis> ,greater<pis> > heap;
    
    dist[start] = 0;
    heap.push({f(start), start}); //估价函数第一关键字
    
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    
    while(heap.size()){
        auto t = heap.top();
        heap.pop();
        
        string state = t.y;
        if(state == end) break;
        
        int x, y;
        for(int i = 0; i < 9; i++)
            if(state[i] == 'x'){
                x = i / 3, y = i % 3; //x的位置
                break;
            }
            
        string source = state; //原状态 存下来 恢复现场
        for(int i = 0 ;i < 4; i++){
            int a = x + dx[i], b = y +  dy[i];
            if(a < 0 || a >= 3 || b < 0 || b >= 3) continue;
            state = source; //每次循环 都恢复原状
            swap(state[x * 3 + y], state[a  *3 + b]);
            if(!dist.count(state) || dist[state] > dist[source] + 1){ //需要被优化
                dist[state] = dist[source] + 1;
                prev[state] = {op[i], source};
                heap.push({dist[state] + f(state),state});
            }
        }
    }
    
    string res;
    while(end != start){
        res += prev[end].x;
        end = prev[end].y;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main(){
    string start, seq;
    char c;
    while(cin >> c){
        start += c;
        if(c != 'x') seq +=c ;
    }
    
    //n^2复杂度求逆序对 由于数据量只有8 所以无所谓
    int cnt = 0;
    for(int i = 0; i < 8; i++)
        for(int j = i; j < 8; j++)
            if(seq[i] > seq[j]) 
                cnt ++;  
                
    if(cnt & 1) puts("unsolvable");
    else cout << bfs(start) << endl;
    
    return 0;
}