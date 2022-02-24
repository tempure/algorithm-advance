#include<bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc189/editorial/592

int a[10010];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)cin >> a[i];

    int ans = 0;
    for (int l = 0; l < n; l++) {
        int x = a[l];
        for (int r = l; r < n; r++) {
            x = min(x, a[r]);
            ans = max(ans, x * (r - l + 1));
        }
    }
    cout << ans;
}