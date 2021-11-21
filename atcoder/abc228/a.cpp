#include <bits/stdc++.h>
using namespace std;

int main() {
    int s, t, x;
    cin >> s >> t >> x;
    if (s < t) {
        cout << (s <= x and x < t ? "Yes" : "No") << '\n';
    } else {
        cout << (x < t or s <= x ? "Yes" : "No") << '\n';
    }
}