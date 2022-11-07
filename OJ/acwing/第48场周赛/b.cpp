#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    string state = "012";
    n %= 6;

    for (int i = 1; i <= n; i ++ ) {
        if (i % 2 == 1) swap(state[0], state[1]);
        else swap(state[1], state[2]);
    }

    cout << state[x] << endl;
    return 0;
}