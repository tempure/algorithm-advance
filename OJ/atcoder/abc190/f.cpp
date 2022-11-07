#include <iostream>
#include <vector>
#include <atcoder/fenwicktree>
using namespace std;
using ll = int64_t;

//https://atcoder.jp/contests/abc190/submissions/19761416

int main() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    for (ll& a : A) cin >> a;
    ll ans = 0;
    atcoder::fenwick_tree<ll> bit(N);
    for (ll a : A) {
        ans += bit.sum(a, N);
        bit.add(a, 1);
    }
    for (ll a : A) {
        cout << ans << '\n';
        ans += N - 1 - a * 2;
    }
}