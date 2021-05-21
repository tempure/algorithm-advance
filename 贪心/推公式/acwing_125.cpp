#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

/*
一个直觉理解：如果一个牛的w+s很大，要么w很大，要么s很大，如果将该牛从上边移到下边
答案都会更优，也可以用邻项交换来证明。
*/

const int N = 50050;
typedef pair<int, int> PII;
int n;
PII cows[N];

//按照每个牛的 wi + si  排序 然后扫描一遍
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int w,  s;
        cin >> w >> s;
        cows[i]  = {w + s, s};
    }
    sort(cows, cows + n);

    int sum = 0, res = INT_MIN;
    for (int i = 0; i < n; i++) {
        res = max(res, sum - cows[i].second); //先更新res再更新sum 因为不能算上当前的 不然会错
        sum += cows[i].first - cows[i].second;
    }

    cout << res << endl;
    return 0;
}