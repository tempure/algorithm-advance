#include<bits/stdc++.h>
#define mod 998244353
using namespace std;

//https://www.bilibili.com/video/BV1Pi4y1C7A5?t=2729.0
//https://atcoder.jp/contests/abc242/editorial/3527

int main() {
  int tc;
  cin >> tc;
  while (tc > 0) {
    tc--;
    int n;
    string s;
    cin >> n >> s;
    long long cres = 0;
    string target = s;
    int p = 0, q = n - 1;
    while (p < q) {
      target[q] = target[p];
      p++; q--;
    }
    int last = (n - 1) / 2;
    for (int i = 0; i <= last; i++) {
      cres *= 26; cres %= mod;
      cres += (s[i] - 'A'); cres %= mod;
    }
    cres++; cres %= mod;
    // if (s < target) {cres += (mod - 1); cres %= mod;}
    if (s < target) cres --;
    cres = (cres + mod) % mod;
    cout << cres << '\n';
  }
  return 0;
}