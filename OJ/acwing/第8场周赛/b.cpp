#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    unordered_map<int, ll>S;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        S[x - i] += x;
    }
    ll res = 0;
    for (auto & [k, v] : S) res = max(res, v);
    cout << res << endl;

    return 0;
}