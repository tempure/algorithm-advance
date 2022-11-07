#include <iostream>
using namespace std;


//DO NOT NEED DSU

int n, x;
int a[100001];
bool b[100001];

int main(void)
{
  cin >> n >> x;
  for (int i = 1; i <= n; i++) cin >> a[i];

  int i = x;
  do {
    b[i] = true;
    i = a[i];
  } while (!b[i]);

  int ans = 0;
  for (int i = 1; i <= n; i++) if (b[i]) ans++;
  cout << ans << endl;

  return 0;
}
