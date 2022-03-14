#include <bits/stdc++.h>
using namespace std;
const int INF = 100000000;

//https://atcoder.jp/contests/abc180/editorial/249
//https://atcoder.jp/contests/abc180/submissions?f.User=SSRS

int main() {
    int N;
    cin >> N;
    vector<int> X(N), Y(N), Z(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i] >> Z[i];
    }
    vector<vector<int>> d(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            d[i][j] = abs(X[j] - X[i]) + abs(Y[j] - Y[i]) + max(0, Z[j] - Z[i]);
        }
    }
    vector<vector<int>> dp(1 << N, vector<int>(N, INF));
    for (int i = 1; i < N; i++) {
        dp[1 << i][i] = d[0][i];
    }
    for (int i = 1; i < (1 << N); i++) {
        for (int j = 0; j < N; j++) {
            if (dp[i][j] != INF) {
                for (int k = 0; k < N; k++) {
                    if (!(i >> k & 1)) {
                        dp[i + (1 << k)][k] = min(dp[i + (1 << k)][k], dp[i][j] + d[j][k]);
                    }
                }
            }
        }
    }
    cout << dp[(1 << N) - 1][0] << endl;
}