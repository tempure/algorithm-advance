#include <bits/stdc++.h>
using namespace std;

//直接前后双指针交换就行了
//https://www.cnblogs.com/Kanoon/p/13423584.html

int main() {
    int n; string s; cin >> n >> s;
    int ans = 0;
    int l = 0, r = n - 1;
    while (l < r) {
        if (s[l] == 'W') {
            while (r > l and s[r] != 'R') --r;
            if (r > l) {
                ++ans;
                ++l;
                --r;
            }
        } else ++l;
    }
    cout << ans << "\n";
}