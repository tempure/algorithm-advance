#include <bits/stdc++.h>
using namespace std;


//题解：https://www.acwing.com/activity/content/code/content/1971096/

//讨论k和3倍数的关系

int main() {
  int t;
  cin >> t;
  while (t --) {
    int n, k;
    cin >> n >> k;
    if (k % 3) {
      if (n % 3) puts("Alice");
      else puts("Bob");
    }
    else {
      n %= k + 1;
      if (n == k || n % 3) puts("Alice");
      else puts("Bob");
    }
  }
  return 0;
}