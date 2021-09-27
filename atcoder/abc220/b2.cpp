//stoi stoll
//https://en.cppreference.com/w/cpp/string/basic_string/stol

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int k;
    string a, b;
    cin >> k >> a >> b;
    cout << 1ll * stoll(a, nullptr, k) * stoll(b, nullptr, k) << endl;
}

int main() {
    solve();
    return 0;
}