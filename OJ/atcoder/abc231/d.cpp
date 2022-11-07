#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;

//要用并查集维护才行，不能只简单统计点的出度和入度
//考虑两个一个度数的点，这俩点都已经被安排了相邻的点，但是此时安排这俩点相邻，也没有超过度数为2，但是不可能这俩相邻了

int main() {
  int n, m;
  cin >> n >> m;
  vector<int>d(n);
  dsu uf(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    if (uf.same(a, b)) {
      cout << "No" << endl;
      return 0;
    }
    uf.merge(a, b);
    d[a]++;
    d[b]++;
  }
  for (int i = 0; i < n; i++)if (d[i] > 2) {
      cout << "No" << endl;
      return 0;
    }
  cout << "Yes" << endl;
}