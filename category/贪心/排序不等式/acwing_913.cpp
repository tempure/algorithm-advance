#include <iostream>
#include <algorithm>
using namespace std;

/*
排队打水问题
可用邻项交换法证明
从小到大将每个人打水需要的时间排序
然后求前缀和数组，最后将前缀和数组的n-1元素求和
*/

const int N = 100010;
int a[N], s[N];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + a[i];
    long long  res = 0;
    for (int i = 1; i <= n; i++) res += s[i - 1]; //每个人不需要等待自身所花的时间

    cout << res << endl;

    return 0;
}