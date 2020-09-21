/*
* @Description: 1012.友好城市
* @Author: Xiaobin Ren
* @Date:   2020-09-21 13:37:25
* @Last Modified time: 2020-09-21 13:37:58
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int > pii;
const int N = 5050;
int f[N];

vector<pii> a;
int n;
//先将每个pair按照第一关键字排序 也就是北岸的
//然后排好序之后 再求一遍第二关键字的LIS 
//做完之后 北岸已经有序 南岸也有序 就不会交叉了
int main(){
    
    cin >> n;
    int x, y;
    for(int i = 0 ; i< n; i++){
        cin >> x >> y;
        a.push_back({x, y});
    } 
    
    sort(a.begin(), a.end());
    
    for(int i = 0; i < n; i++){
        f[i] = 1;
        for(int j = 0; j < i; j++)
            if(a[j].second < a[i].second) f[i] = max(f[i], f[j] + 1);
    }
    int res  = 0;
    for(int i = 0; i < n; i++) res = max(res, f[i]);
    
    cout << res << endl;
    return 0;
}