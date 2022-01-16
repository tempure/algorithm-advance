#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;


//https://atcoder.jp/contests/abc235/editorial/3264
//https://atcoder.jp/contests/abc235/submissions/28551502

const int N = 1000005;
int a, n;
int d[N];
int q[N], t;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  cin >> a >> n;
  memset(d, -1, sizeof d);
  d[1] = 0, q[t = 1] = 1;
  for (int i = 1; i <= t; i++) {
    int x = q[i];
    long long y = 1ll * x * a; //乘操作
    if (y < 1000000 && d[y] == -1) {
      d[y] = d[x] + 1;
      q[++t] = y;
    }
    if (x > 10 && x % 10) { //第二种操作
      int y = x % 10;
      int z = x / 10;
      int tt = 1;
      while (tt <= z)
        tt *= 10;
      y = y * tt + z;
      if (d[y] == -1) {
        d[y] = d[x] + 1;
        q[++t] = y;
      }
    }
  }

  cout << d[n];
}