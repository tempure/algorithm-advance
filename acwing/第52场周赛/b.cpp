#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//前后分别扫一遍就行了 O(N)
//单调栈也能做 但没必要

const int N = 200010;

int n;
int q[N], ans[N];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &q[i]);

    for (int i = 0, last = -n; i < n; i ++ )
    {
        if (!q[i]) last = i;
        ans[i] = i - last;
    }

    for (int i = n - 1, last = n * 2; i >= 0; i -- ) //last初始设为无穷 够大/够小就行了
    {
        if (!q[i]) last = i;
        ans[i] = min(ans[i], last - i);
    }

    for (int i = 0; i < n; i ++ )
        printf("%d ", ans[i]);

    return 0;
}

// 作者：yxc
// 链接：https://www.acwing.com/activity/content/code/content/3501072/
// 来源：AcWing
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。