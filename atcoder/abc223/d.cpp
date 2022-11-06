#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, M = N;
int h[N], e[M], ne[M], idx;
int d[N], path[N];
int n, m;
int cnt;


//如果要求最小字典序的拓扑排序，那么直接改用优先队列即可！
priority_queue<int, vector<int>, greater<int> > q;

void add(int a, int b) {
  e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool topsort() {
  for (int i = 1; i <= n; i++)
    if (d[i] == 0) q.push(i);
  while (q.size()) {
    int t = q.top();
    path[cnt++] = t;
    q.pop();
    for (int i = h[t]; i != -1; i = ne[i]) {
      int j = e[i];
      if (-- d[j] == 0) q.push(j);
    }
  }
  return cnt == n ;
}

int main() {
  cin >> n >> m;
  memset(h, -1, sizeof h);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    add(a, b);
    d[b]++;
  }
  if (topsort()) {
    for (int i = 0; i < cnt; i++) cout << path[i] << ' ';
  }
  else puts("-1");
}