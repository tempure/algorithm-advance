#include<bits/stdc++.h>
using namespace std;

//这个就是双指针扫描啊。。。哪里是sliding window。。。都不是单调队列

long long f(long long a, long long b) {
  return (a * a * a + a * a * b + a * b * b + b * b * b);
}

int main() {
  long long n;
  cin >> n;
  long long x = 8e18;
  long long i = 0, j = 1000000;
  while (i <= j) {
    long long cf = f(i, j);
    if (cf >= n) {x = min(x, cf); j--;}
    else {i++;}
  }
  cout << x << '\n';
  return 0;
}