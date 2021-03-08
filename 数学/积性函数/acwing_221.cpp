#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);

    ll res = n;
    for (int i = 2; i <= n / i; i++)
        if (n % i == 0) { //i是n的一个质因子
            int a = 0, p = i;
            while (n % p == 0) a ++, n /= p; //a统计次数
            res = res * (p + (ll)a * p - a) / p; //通分 不要用小数
        }

    //最后还有一个质因子
    if (n > 1) res = res * ((ll)n + n - 1) / n;
    cout << res << endl;

    return 0;
}