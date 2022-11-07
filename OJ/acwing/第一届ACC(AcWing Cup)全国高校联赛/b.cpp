#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210;

int n, m;
int p[N];

int main()
{
    int T;
    cin >> T;
    while (T -- )
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i ++ ) cin >> p[i];

        int res = max(p[1], n - p[m] + 1);
        for (int i = 1; i < m; i ++ )
            res = max(res, (p[i] + p[i + 1]) / 2 - p[i] + 1);
        cout << res << endl;
    }

    return 0;
}