#include <iostream>
#include <algorithm>
using namespace std;

//经典货仓选址，中位数
//注意下标从1开始 中位数位置 x = (n + 1) / 2

const int N = 1e5 + 10;
int a[N];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a, a + n);

    int x = (n + 1) / 2;

    long long res = 0;
    for (int i = 1; i <= n; i++) {
        res += abs(a[i] - a[x]);
    }

    cout << res << endl;

    return 0;
}