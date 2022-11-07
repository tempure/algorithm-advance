#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;  //复制一倍长度
int n, a[N], q[N]; //q[] 队列下标


/*
不知道为啥这题会和DP有关系。。。就是一个很裸的单调队列滑动窗口

首先对于这种环上问题，而且要维护固定长度区间的问题，直接考虑复制一遍拆环

那么对于 a[i] + a[j] + dist(i,j) -> a[i] + i + (a[j] - j), (i - j <= n / 2)
只考虑所有n/2长度区间即可, 上面式子改写后，对于一个i，在i结尾的长度为 n/2
长度区间内，找到最大的 a[j] - j 即可，用单调队列或者堆都可以，此题用堆多一个log超时
*/

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[n + i] = a[i];
    }
    int l = 1, r = 1;
    q[1] = 0;
    int ans = 0;
    for (int i = 1; i <= n * 2; i++) {
        while (l <= r && q[l] < i - n / 2) l++;
        ans = max(ans , a[i] + i + a[q[l]] - q[l]);
        // i即将增长为i+1，i本身作为决策插入
        while (l <= r && a[i] - i >= a[q[r]] - q[r]) r --;
        q[++r] = i;
    }
    cout << ans << endl;
    return 0;
}