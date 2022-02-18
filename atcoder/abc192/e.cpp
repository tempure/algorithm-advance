#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc192/submissions/20408532
//https://atcoder.jp/contests/abc192/editorial/764

int main() {
  int N, M, X, Y;
  cin >> N >> M >> X >> Y;
  X--;
  Y--;
  vector<vector<tuple<long long, long long, int>>> E(N);
  for (int i = 0; i < M; i++) {
    int A, B;
    long long T, K;
    cin >> A >> B >> T >> K;
    A--;
    B--;
    E[A].push_back(make_tuple(T, K, B));
    E[B].push_back(make_tuple(T, K, A));
  }
  vector<long long> d(N, -1);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
  pq.push(make_pair(0, X));
  while (!pq.empty()) {
    long long dd = pq.top().first;
    int v = pq.top().second;
    pq.pop();
    if (d[v] == -1) {
      d[v] = dd;
      for (auto e : E[v]) {
        long long T = get<0>(e);
        long long K = get<1>(e);
        int w = get<2>(e);
        if (d[w] == -1) {
          pq.push(make_pair((dd + K - 1) / K * K + T, w));
        }
      }
    }
  }
  cout << d[Y] << endl;
}