#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*贪心
反向思考 从m转换为n，反向操作

n>m,最优方法是一直减1，返回n-m；
n<m分组讨论：
1.m为奇数，让m+1然后除以2；
2.当m为偶数，直接除以2

证明：分类讨论思路的正确性
假设 n = (m + k) / 2, 从m -> n
那么先除后加: m / 2 + k / 2 -> 1 + k/2 步
先加后除: (m+k)/2 -> k + 1 步 显然第一种更优
*/

const int N = 20010;

int n, m;

int main() {
    cin >> n >> m;

    int res = 0;
    while (m != n) {
        if (m < n) m ++ ;
        else if (m & 1) m ++ ;
        else m /= 2;
        res ++ ;
    }

    cout << res << endl;

    return 0;
}