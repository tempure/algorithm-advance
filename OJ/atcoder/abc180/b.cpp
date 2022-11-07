#include <bits/stdc++.h>
using namespace std;

//这种计算题 有病吧

int main() {
    cout << fixed << setprecision(15);

    int n;
    cin >> n;
    vector<int>x(n);
    for (int i = 0; i < n; i++)cin >> x[i];

    long ans1 = 0;
    for (int i = 0; i < n; i++)ans1 += abs(x[i]);
    cout << ans1 << endl;

    long ans2 = 0;
    for (int i = 0; i < n; i++)ans2 += abs(x[i]) * (long)abs(x[i]);
    cout << sqrt(ans2) << endl;

    int ans3 = 0;
    for (int i = 0; i < n; i++)ans3 = max(ans3, abs(x[i]));
    cout << ans3 << endl;
}
