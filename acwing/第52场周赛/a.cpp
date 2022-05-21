#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    int res = 0;
    for (int i = 1; ; i ++ ) {
        int t = i * (i + 1) / 2;
        if (t > n) break;
        res ++ ;
        n -= t;
    }

    cout << res << endl;
    return 0;
}