#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc184/editorial/374
//又是一道谜语人题

int main() {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    int r = r2 - r1, c = c2 - c1;
    int ans = 3;
    if (!r && !c) ans = 0;
    else if (r == c || r == -c || abs(r) + abs(c) <= 3) ans = 1;
    else if ((r ^ c ^ 1) & 1 || abs(r + c) <= 3 || abs(r - c) <= 3 || abs(r) + abs(c) <= 6) ans = 2;
    cout << ans << endl;
}