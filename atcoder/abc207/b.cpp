#include<bits/stdc++.h>
using namespace std;

int main() {
    long long A, B, C, D; cin >> A >> B >> C >> D;
    long long blue = A, red = 0;
    for (int i = 1; i <= A; i++) {
        blue += B;
        red += C;
        if (blue <= D * red) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
