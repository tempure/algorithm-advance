#include<bits/stdc++.h>
#define mod 998244353

using namespace std;

//https://atcoder.jp/contests/abc246/editorial/3713
//why the answer is the number of distinct alphabets that can be typed with all rows in S ?
//不是每次只能从1行里面选吗，容斥倒是没什么问题
//假设N=3
//aaa
//bbb
//ccc 那么这样确实答案是对的。。。。数学好差不太能理解 power(c,k) 这个次幂具体代表什么字符串的组合


/*
哦我好像懂了。。。。。
在容斥奇数项相加的里面，也就是计算单行贡献的项，
所有的行不同的字符数一起 power(c,k)的结果，和单行计算然后加起来没有区别
假设长度为k，对于单行来说，字符串每个位置都有x种选法，x是当前行的不同字符数量
那么加起来就是所有行不同的字符数量咯。。。。。
*/

long long power(long long a, long long b) {
  long long x = 1, y = a;
  while (b > 0) {
    if (b & 1ll) {
      x = (x * y) % mod;
    }
    y = (y * y) % mod;
    b >>= 1;
  }
  return x % mod;
}

int main() {
  int n, k;
  cin >> n >> k;
  vector<int> v(n, 0);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (auto &nx : s) {v[i] |= (1 << (nx - 'a'));}
  }

  long long res = 0;
  for (int i = 1; i < (1 << n); i++) {
    int ch = (1 << 26) - 1;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {ch &= v[j];}
    }
    int pc = __builtin_popcount((unsigned int)ch);

    //why power(pc, k) ?? 注释说明了
    if (__builtin_popcount((unsigned int)i) % 2) {res += power(pc, k); res %= mod;}
    else {res += (mod - power(pc, k)); res %= mod;}
  }

  cout << res << '\n';
  return 0;
}