#include <bits/stdc++.h>
using namespace std;

//枚举就行了。。。
//https://atcoder.jp/contests/abc249/submissions/31176201

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  vector<int> cnt(200001, 0);
  for (int i = 0; i < N; i++) {
    cnt[A[i]]++;
  }
  long long ans = 0;
  for (int i = 1; i <= 200000; i++) {
    for (int j = i; j <= 200000; j += i) {
      ans += (long long) cnt[i] * cnt[j / i] * cnt[j]; // j/i
    }
  }
  cout << ans << endl;
}