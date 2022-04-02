#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    int a[4];
    for (int i = 0; i < 4; i ++ ) cin >> a[i];

    int res = 0;
    string s;
    cin >> s;

    for (auto c : s)
        res += a[c - '1'];

    cout << res << endl;
    return 0;
}