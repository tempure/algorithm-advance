#include <bits/stdc++.h>
using namespace std;

long long Cn_2(int i) {
    return 1LL * i * (i - 1) / 2;
}

int main()
{
    int n, m; cin >> n >> m;
    cout << Cn_2(n) + Cn_2(m);
    return 0;
}