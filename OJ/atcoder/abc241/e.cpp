#include <bits/stdc++.h>
using namespace std;

using lint = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    lint K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    vector<int> nxt(N);
    vector<lint> sum(N);
    for (int i = 0; i < N; i++) {
        nxt[i] = (i + A[i]) % N;
        sum[i] = A[i];
    }
    int pos = 0;
    lint ans = 0;
    for (int b = 0; b < 40; b++) {
        if ((K >> b) & 1) {
            ans += sum[pos];
            pos = nxt[pos];
        }
        vector<int> nxt2(N);
        vector<lint> sum2(N);
        for (int i = 0; i < N; i++) {
            nxt2[i] = nxt[nxt[i]];
            sum2[i] = sum[i] + sum[nxt[i]];
        }
        nxt = nxt2;
        sum = sum2;
    }
    cout << ans << '\n';
    return 0;
}