#include <iostream>
using namespace std;

//普通NIM博弈

int main() {
    int n; cin >> n;
    int res = 0;
    for (int i = 0 ; i < n; i++) {
        int x; cin >> x;
        res ^= x;
    }

    if (res == 0)puts("No");
    else puts("Yes");

    return 0;
}