#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    sort(v.begin(), v.end(), greater<int>());

    // for(auto t : v){
    //     cout << t << ' ';
    // }
    // cout<< endl;
    for (auto t : v) {
        if ((int)((int)sqrt(t)*(int)sqrt(t)) != t) {
            cout << t << endl;
            break;
        }
    }
}

int main() {
    int t = 1;
    //cin >> t;
    while (t --) solve();
    return 0;
}
