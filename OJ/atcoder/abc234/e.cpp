#include<bits/stdc++.h>

using namespace std;

//https://atcoder.jp/contests/abc234/editorial/3234

set<long long> gen_tosasu() {
  set<long long> res;
  for (int fir = 1; fir <= 9; fir++) {
    for (int d = -9; d <= 8; d++) {
      string s;
      int dg = fir;
      for (int i = 0; i < 18; i++) {
        s.push_back(dg + '0');
        res.insert(stoll(s));
        dg += d;
        if (!(0 <= dg && dg <= 9)) {break;}
      }
    }
  }
  return res;
}

int main() {
  long long x;
  cin >> x;
  set<long long> st = gen_tosasu();
  // for (auto t : st) {
  //   cout << t << endl;
  //   cout << "***";
  // }
  cout << (*st.lower_bound(x)) << '\n';
  return 0;
}