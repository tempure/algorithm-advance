#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    map<int, int> pos;

    for (int i = 1; i <= n; i ++ )
    {
        int x;
        cin >> x;
        pos[x] = i;
    }

    if (pos.size() < 3) puts("-1 -1 -1");
    else
    {
        vector<int> res;
        for (auto [k, v] : pos) res.push_back(v);
        for (int i = 0; i < 3; i ++ )
            cout << res[i] << ' ';
        cout << endl;
    }

    return 0;
}