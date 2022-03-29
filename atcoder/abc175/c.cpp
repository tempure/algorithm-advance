#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

//奇偶讨论
//https://atcoder.jp/contests/abc175/editorial/71

int main() {
    ll X, K, D;
    cin >> X >> K >> D;
    X = abs(X);

    ll straight = min(K, X / D);
    K -= straight;
    X -= straight * D;

    if (K % 2 == 0) {
        cout << X << endl;
    } else {
        cout << D - X << endl;
    }

    return 0;
}