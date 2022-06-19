#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int n, m;
int a[N];

//题意有点模糊
//每场只选2个选手，所以可以一个选手和多个选手格斗
//https://www.acwing.com/video/3977/

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);
    sort(a, a + n);

    int res = n;
    for (int i = 0, j = 0; i < n; i ++ ) {
        while (j < n && a[j] - a[i] <= m) j ++ ;
        if (a[j - 1] > a[i]) res -- ;
    }

    printf("%d\n", res);
    return 0;
}