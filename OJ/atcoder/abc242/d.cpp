#include<bits/stdc++.h>
using namespace std;
using ll = long long;

//https://atcoder.jp/contests/abc242/editorial/3528
//这题解写的言语混乱有些地方矛盾
//第一句开幕雷击就有问题，建议看医生

int main() {
    string S; cin >> S;
    int Q; cin >> Q;
    auto g = [&](char s, ll add) {
        return char('A' + (s - 'A' + add) % 3);
    };
    std::function<char(ll, ll)> f = [&](ll t, ll k) {
        if (t == 0) return S[k];
        if (k == 0) return g(S[0], t);
        return g(f(t - 1, k / 2), k % 2 + 1);
    };
    while (Q--) {
        ll t, k; cin >> t >> k;
        cout << f(t, k - 1) << endl;
    }
    return 0;
}