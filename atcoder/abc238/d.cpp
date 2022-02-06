#include<bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc238/editorial/3369
//https://www.bilibili.com/video/BV1sL4y1s71M

/*
x&y=a那么x=a,y=a,即s=2a,所以s<2a的直接输出No.s-2a这个部分就得分配到x和y,
但如果它和a有同为1的位,无论怎么分配会影响a的值,所以得保证a&(s-2a)=0.
*/

using ll = long long;

int main() {
    ll T; cin >> T;
    while (T--) {
        ll a, s; cin >> a >> s;
        string ans = "No";
        if (2 * a <= s) {
            ll differ = s - 2 * a;
            if ((differ & a) == 0) ans = "Yes";
        }
        cout << ans << endl;
    }
    return 0;
}