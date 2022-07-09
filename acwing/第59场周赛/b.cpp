#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

//偶数直接一直减2 减到 0
//奇数减去最小的质因数，然后一直减2减到0

int main() {
    LL n;
    cin >> n;

    LL res = 0;
    if (n % 2) {
        for (int i = 2; i <= n / i; i ++ )
            if (n % i == 0) {
                n -= i;
                res ++ ;
                break;
            }

        if (n % 2) res ++, n = 0; // n 是质数
    }

    res += n / 2;
    cout << res << endl;

    return 0;
}