#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc199/submissions/21997408
//https://atcoder.jp/contests/abc199/tasks/abc199_c/editorial

int main() {
  int N;
  cin >> N;
  string S;
  cin >> S;
  int Q;
  cin >> Q;
  bool f = false;
  for (int i = 0; i < Q; i++) {
    int T, A, B;
    cin >> T >> A >> B;
    if (T == 1) {
      A--;
      B--;
      if (f) {
        A = (A + N) % (N * 2);
        B = (B + N) % (N * 2);
      }
      swap(S[A], S[B]);
    }
    if (T == 2) {
      f = !f;
    }
  }
  if (f) {
    S = S.substr(N) + S.substr(0, N);
  }
  cout << S << endl;
}