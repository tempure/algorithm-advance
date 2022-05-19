#include <bits/stdc++.h>
using namespace std;

long long Cn_2(int i) {
    return 1LL * i * (i - 1) / 2;
}

int main()
{
    map<int, int> m;
    int n; cin >> n;
    int a[n]; for (int & i : a) cin >> i, ++ m[i];

    long long sum = 0;
    for (auto i : m) sum += Cn_2(i.second);

    for (int i : a)
        cout << sum - Cn_2(m[i]) + Cn_2(m[i] - 1) << "\n";

    return 0;
}