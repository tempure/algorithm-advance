#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    char last = s[0];
    cout << s[0];
    for (int i = 1; s[i]; i++) {
        if (s[i] == last) continue;
        cout << s[i];
        last = s[i];
    }
}
