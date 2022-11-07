#include <atcoder/modint>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using Modint = atcoder::modint998244353;

//https://atcoder.jp/contests/abc244/editorial/3619

int main() {
    int N, M, K, S, T, X;
    cin >> N >> M >> K >> S >> T >> X;
    S--; T--; X--;
    vector<pair<int, int>> edge(M);
    for (auto& [U, V] : edge) {
        cin >> U >> V;
        U--; V--;
    }
    vector dp(K + 1, vector(N, array<Modint, 2> {0, 0}));
    dp[0][S][0] = 1;
    for (int i = 0; i < K; i++) {
        for (auto [U, V] : edge) for (int x : {0, 1}) {
                dp[i + 1][V][x ^ (V == X)] += dp[i][U][x];
                dp[i + 1][U][x ^ (U == X)] += dp[i][V][x];
            }
    }
    cout << dp[K][T][0].val() << endl;
}