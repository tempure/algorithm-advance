#include<bits/stdc++.h>

//谜语人题
//https://atcoder.jp/contests/abc246/editorial/3710

using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    int d2 = x * x + y * y;
    double d = d2;
    d = sqrt(d);
    double dx = x, dy = y;
    cout << dx / d << ' ' << dy / d << '\n';
    return 0;
}
