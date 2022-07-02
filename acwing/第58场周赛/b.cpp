#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int n;
int w[N];

//思维题
//如果 w[i] <= w[i-1] * 2 那么 w[i-1]必选，因为序列是递增的，选比不选一定更优

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &w[i]);

    int res = 0;
    for (int i = 0; i < n; i ++ ) {
        int j = i + 1;
        while (j < n && w[j] <= w[j - 1] * 2) j ++ ;
        res = max(res, j - i);  //此时 j是一个不合法位置，j-1是合法序列末尾元素
        i = j - 1;
    }

    printf("%d\n", res);
    return 0;
}