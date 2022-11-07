#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 4;
int a[MAXN];

int main() {
    int k, n;
    cin >> k >> n;

    int maxx = 0;
    cin >> a[0];
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        maxx = max(maxx, a[i] - a[i - 1]);
    }
    maxx = max(maxx, k + a[0] - a[n - 1]);

    cout << k - maxx << endl;

    return 0;
}