#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//询问连通块数量最多才1e6, 直接暴力询问

signed main() {
    ll n, q; cin >> n >> q;
    ll nil = -1;
    vector<ll>front(n + 1, nil); // front[i] := The train jointed in front of Train i, or nil if there's no such train.
    vector<ll>back(n + 1, nil); // back[i]  := The train jointed in back of Train i, or nil if there's no such train.
    while (q--) {
        ll c; cin >> c;
        if (c == 1) {
            ll x, y; cin >> x >> y;
            back[x] = y;
            front[y] = x;
        } else if (c == 2) {
            ll x, y; cin >> x >> y;
            back[x] = nil;
            front[y] = nil;
        } else {
            ll x; cin >> x;
            while (front[x] != nil) {
                x = front[x]; // Move to the first of the connected component of x
            }
            vector<ll>ans;
            while (x != nil) {
                ans.push_back(x);
                x = back[x];
            }
            cout << ans.size() << " ";
            for (ll i = 0; i <= (int)ans.size() - 1; i++) {
                cout << ans[i];
                if (i != (int)ans.size() - 1)cout << " ";
                else cout << endl;
            }
        }
    }

    return 0;
}
