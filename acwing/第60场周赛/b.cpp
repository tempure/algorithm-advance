#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, k;
int w[N];

//注意审题：并让数组中的所有"非零元素"都减去
//减到0的前面所有都保持0不变

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    sort(w + 1, w + n + 1);
    n = unique(w + 1, w + n + 1) - w - 1; //去重

    for (int i = 1; i <= k; i ++ )
        if (i <= n) printf("%d\n", w[i] - w[i - 1]);
        else printf("%d\n", 0);  //操作次数比去重后的数组长度都大，最后的都是重复的，全部都是减为0
    return 0;
}