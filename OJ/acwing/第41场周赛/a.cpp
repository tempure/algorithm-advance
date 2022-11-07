#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;

    string res(20, 'z');
    for (int i = 1; i <= a.size(); i ++ )
        for (int j = 1; j <= b.size(); j ++ )
            res = min(res, a.substr(0, i) + b.substr(0, j));

    cout << res << endl;
    return 0;
}