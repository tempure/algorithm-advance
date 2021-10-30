#include <bits/stdc++.h>
using namespace std;

int64_t pow10(int n) {
    return n <= 0 ? 1 : 10 * pow10(n - 1);
}

void run_case() {
    int N;
    int64_t K;
    cin >> N >> K;
    K++;
    vector<int> A(N);

    for (auto &a : A)
        cin >> a;

    sort(A.begin(), A.end());
    A.push_back(18);
    int64_t ans = 0;

    for (int i = 0; i < N; i++) {
        int64_t most = pow10(A[i + 1] - A[i]) - 1; //当前单位纸币最多能拿多少张，-1是因为不减的话就可以用一张A[i+1]的代替
        int64_t take = min(most, K);
        K -= take;
        ans += take * pow10(A[i]);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests-- > 0)
        run_case();
    return 0;
}