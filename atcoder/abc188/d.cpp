#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

//https://atcoder.jp/contests/abc188/editorial/556
//这题tm到底啥意思啊。。。。不知道想表达什么。。。
//翻译的也是莫名其妙的。。。

int main() {
    ll N, C;
    cin >> N >> C;
    vector<pair<ll, ll>> event;
    for (ll i = 0; i < N; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        event.emplace_back(a - 1, c);
        event.emplace_back(b, -c);
    }
    sort(event.begin(), event.end());
    ll ans = 0, fee = 0, t = 0;
    for (auto [x, y] : event) {
        if (x != t) {
            ans += min(C, fee) * (x - t);
            t = x;
        }
        fee += y;
    }
    cout << ans << endl;
}