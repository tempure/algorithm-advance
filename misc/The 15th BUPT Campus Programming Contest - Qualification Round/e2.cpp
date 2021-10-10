#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define int unsigned long long
const int N = 1000005;

string s;
int n, m;
int a[N];
int b[N];

signed main() {
  int i, j;
  cin >> s;
  n = s.size();
  printf("f'(x)=");
  i = 5;
  m = 1;
  while (i < n) {
    if (s[i] == '-') {
      j = -1;
      i++;
    }
    else {
      j = 1;
      if (s[i] == '+')
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9') {
      a[m] = a[m] * 10 + s[i] - '0';
      i++;
    }
    if (a[m] == 0)
      a[m] = j;
    else
      a[m] *= j;
    if (s[i] == 'x') {
      i++;
      if (s[i] == '^') {
        i++;
        while (s[i] >= '0' && s[i] <= '9') {
          b[m] = b[m] * 10 + s[i] - '0';
          i++;
        }
      }
      else
        b[m] = 1;
    }
    else
      b[m] = 0;
    m++;
  }
  if (m == 2 && (a[1] == 0 || b[1] == 0)) {
    printf("0");
    return 0;
  }
  //for(i=1;i<m;i++)
  //printf("%d %d\n",a[i],b[i]);
  if (a[1] == 1 && b[1] == 1)
    printf("1");
  if (a[1] == -1 && b[1] == 1)
    printf("-1");
  if (a[1]*b[1] > 1)
    printf("%d", a[1]*b[1]);
  if (b[1] == 2)
    printf("x");
  if (b[1] > 2)
    printf("x^%d", b[1] - 1);
  for (i = 2; i < m; i++) {
    if (b[i] == 0)
      continue;
    if (a[i] == 1 && b[i] == 1) {
      printf("+1");
      continue;
    }
    if (a[i] == -1 && b[i] == 1) {
      printf("-1");
      continue;
    }
    if (a[i]*b[i] > 0)
      printf("+");
    if (a[i]*b[i] != 1 || a[i]*b[i] != -1)
      printf("%d", a[i]*b[i]);
    if (b[i] == 2)
      printf("x");
    if (b[i] > 2)
      printf("x^%d", b[i] - 1);
  }
  return 0;
}

