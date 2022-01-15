#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

//https://codeforces.com/blog/entry/59281
//https://www.acwing.com/activity/content/code/content/2319126/
//后一个比前一个2的因子多1但是3的因子少1 这种情况不存在，因为就会变成 3/2 倍
int count3(LL x) {
  int ret = 0;
  while (x % 3 == 0) {
    ret++;
    x /= 3;
  }
  return ret;
}
int n;
vector<pair<int, LL>> v;
int main() {
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i].second;
    v[i].first = -count3(v[i].second);
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < n; i++)
    printf("%lld%c", v[i].second, " \n"[i + 1 == n]);
}