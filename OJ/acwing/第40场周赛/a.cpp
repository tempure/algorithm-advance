#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int n;
int f[N];
bool st[N];

int main() {
    cin >> n;
    f[0] = f[1] = 1;
    st[1] = true;
    for (int i = 2; f[i - 1] <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
        st[f[i]] = true;
    }
    for (int i = 1; i <= n; i++)
        if (st[i]) cout << 'O';
        else cout << 'o';
    return 0;
}
