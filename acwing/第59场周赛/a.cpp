#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    int minsum = 0, sum = 0;
    while (n -- ) {
        int x;
        cin >> x;
        sum += x;
        minsum = min(minsum, sum);
    }

    cout << sum - minsum << endl;
    return 0;
}