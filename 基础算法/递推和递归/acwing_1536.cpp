#include <iostream>
using namespace std;

//均分纸牌 直接递推即可
//从左到右递推，当前堆左边的所有堆都已经满足，那么只能向右边的索取或者给予

const int N = 110;
int a[N];

int main() {
    int n; cin >> n;
    int tot = 0;
    for (int i =  1; i <= n; i++) cin >> a[i], tot += a[i];

    int avg = tot / n;
    int ans = 0;

    for (int i = 1; i <= n; i++)
        if (a[i] != avg) {
            a[i + 1] += a[i] - avg;
            ans++;
        }
    cout << ans << endl;

    return 0;
}