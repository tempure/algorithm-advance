/*
* @Description: 1016. 最大上升子序列和
* @Author: Xiaobin Ren
* @Date:   2020-09-21 13:56:18
* @Last Modified time: 2020-09-21 13:56:30
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pii;

const int N = 1010;
vector<pii> a;
//用第一关键字保存元素的值
//第二关键字维护上升子序列的最大值
int main(){
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        a.push_back({x, 0});
    }
    
    for(int i = 0 ; i < n; i++){
        a[i].second = a[i].first;
        for(int j = 0 ; j < i; j++)
            if(a[j].first < a[i].first) a[i].second = max(a[i].second, a[j].second + a[i].first);
    }
    int res = 0;
    for(int i = 0; i < n; i++) res = max(res, a[i].second);
    
    cout << res << endl;
    
    return 0;
}