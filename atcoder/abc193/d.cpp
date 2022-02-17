#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
using ll = int64_t;

//不是很读懂题意，这题好迷。。。

ll score(string S) {
    vector<ll> cnt(10);
    iota(cnt.begin(), cnt.end(), 0);
    for (char c : S) cnt[c - '0'] *= 10;
    return accumulate(cnt.begin(), cnt.end(), 0);
}
int main() {
    ll K;
    string S, T;
    cin >> K >> S >> T;
    vector<ll> cnt(10, K);
    for (char c : S + T) cnt[c - '0']--;
    ll win = 0;
    for (ll x = 1; x <= 9; x++) for (ll y = 1; y <= 9; y++) {
            S.back() = '0' + x;
            T.back() = '0' + y;
            if (score(S) <= score(T)) continue;
            win += cnt[x] * (cnt[y] - (x == y));
        }
    const ll rem = 9 * K - 8;
    cout << double(win) / rem / (rem - 1) << endl;
}
