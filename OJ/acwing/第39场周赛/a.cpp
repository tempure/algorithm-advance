#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int res = 0;
    while (n -- )
    {
        int x;
        cin >> x;
        res += abs(x);
    }

    cout << res << endl;
    return 0;
}