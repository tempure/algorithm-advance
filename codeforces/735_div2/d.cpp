#include <bits/stdc++.h>
using namespace std;
using ll = long long;


void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n / 2; i++) cout << 'a';
    cout << 'b';
    for (int i = 0; i < n / 2 - 1; i++)  cout << 'a';
    if ((n & 1) && n > 1) cout << 'c';
    cout << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while ( t--) solve();
    return 0;
}