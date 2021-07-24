#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 200010;

int w[N];

void solve() {
    int m;
    cin >> m;
    unordered_map<int , pii> S;
    for (int i = 1; i <= m; i++) {
        int n, sum = 0;
        cin >> n;
        for (int j = 1; j <= n; j++) {
            cin >> w[j];
            sum += w[j];
        }
        for (int j = 1; j <= n; j++) {
            int t = sum - w[j];
            if (S.count(t) && S[t].first != i) {
                cout << "YES" << endl;
                printf("%d %d\n", S[t].first, S[t].second);
                printf("%d %d\n", i, j);
                return;
            }
            S[t] = {i, j};
        }
    }
    cout << "NO" << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
}