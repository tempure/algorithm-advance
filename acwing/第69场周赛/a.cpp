#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;

    while (T -- ) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        int d = y - x;
        if (d % (a + b) == 0) cout << d / (a + b) << endl;
        else puts("-1");
    }

    return 0;
}