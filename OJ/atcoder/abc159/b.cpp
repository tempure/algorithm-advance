#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s, r_s;
    cin >> s;
    r_s = s;
    reverse(r_s.begin(), r_s.end());
    if (s == r_s) {
        s = s.substr(0, s.size() / 2);
        r_s = s;
        reverse(r_s.begin(), r_s.end());
        if (s == r_s) return 0 * puts("Yes");
    }
    return 0 * puts("No");
}