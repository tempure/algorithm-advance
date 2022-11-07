#include <iostream>
#include <algorithm>
using namespace std;

int n;
long long a[30], x, ans, t = 1;

int main()
{
    cin >> n >> x;
    for (int i = 0; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
    {
        ans += a[i] * i * t;
        t *= x;
    }
    cout << ans << endl;
    return 0;
}
