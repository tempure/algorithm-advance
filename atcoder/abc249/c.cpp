#include <bits/stdc++.h>
using namespace std;

//谜语题
//没太理解在说啥
//https://atcoder.jp/contests/abc249/submissions/31175712

int main() {
  int N, K;
  cin >> N >> K;
  vector<string> S(N);
  for (int i = 0; i < N; i++) {
    cin >> S[i];
  }
  int ans = 0;
  for (int i = 0; i < (1 << N); i++) {
    vector<int> cnt(26, 0);
    for (int j = 0; j < N; j++) {
      if ((i >> j & 1) == 1) {
        int L = S[j].size();
        for (int k = 0; k < L; k++) {
          cnt[S[j][k] - 'a']++;
        }
      }
    }
    int cnt2 = 0;
    for (int j = 0; j < 26; j++) {
      if (cnt[j] == K) {
        cnt2++;
      }
    }
    ans = max(ans, cnt2);
  }
  cout << ans << endl;
}