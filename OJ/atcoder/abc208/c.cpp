#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// iota : https://en.cppreference.com/w/cpp/algorithm/iota

int main() {
  int N;
  long long K;
  cin >> N >> K;

  vector<int> a(N);
  for (auto& x : a) cin >> x;

  vector<int> order(N);
  iota(begin(order), end(order), 0);
  sort(begin(order), end(order), [&](int i, int j) { return a[i] < a[j]; });

  // for (auto t : order) cout << t << ' ';
  // cout << endl;

  vector<long long> answer(N, K / N);
  for (int i = 0; i < K % N; i++) answer[order[i]]++;

  for (auto&x : answer) cout << x << "\n";
}