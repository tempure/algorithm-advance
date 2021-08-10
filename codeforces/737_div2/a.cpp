#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 10;
int a[N];

void solve() {
    int n;
    cin >> n;
    int max = -2e9;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        if (a[i] > max) max = a[i];
    }
    double res = 0;
    res = max + (sum - max) * 1.0 / (n - 1);
    printf("%.9lf\n", res); 
}

int main() {
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}