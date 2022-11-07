#include<bits/stdc++.h>
using namespace std;


int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int ans = b - a;
        for (int a1 = a; a1 < b; a1++) {
            int b1 = 0;
            for (int i = 21; i >= 0; i--) {
                if ((b >> i) & 1) {
                    b1 ^= (1 << i);
                } else {
                    if ((a1 >> i) & 1) {
                        b1 ^= (1 << i);
                        break;
                    }
                }
            }
            ans = min(ans, a1 - a - b + (a1 | b1) + 1);
        }
        cout << ans << '\n';
    }
}