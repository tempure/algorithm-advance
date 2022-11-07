#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n, s;
    cin >> n >> s;
    if (n == 1) {
        cout << s << '\n';
        return;
    }
    int poz = 0;
    vector<int> v(s);
    for (int i = 0; i < s; ++i)
        v[i] = 0;
    for (int i = 100000000; i >= 1; i /= 10) {
        while (n >= i && (n - i) >= (s - poz - 1)) {
            v[poz] += i;
            n -= i;
            ++poz;
            if (poz == s)
                poz = s - 1;
        }
    }
    for (int i = 0; i < s; ++i)
        cout << v[i] << " ";
    cout << '\n';
}

int main() {
    int  t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}