#include <bits/stdc++.h>
using namespace std;

//直接全排列然后check即可 一共才24种所有走法

const int N = 55;
char g[N][N];
string path;
int n, m;

bool check(vector<int>& q)
{
    int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    int x, y;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ )
            if (g[i][j] == 'S')
                x = i, y = j;

    for (auto c : path)
    {
        int t = q[c - '0'];
        x += dx[t], y += dy[t];
        if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == '#')
            return false;
        if (g[x][y] == 'E') return true;
    }

    return false;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i ++ ) cin >> g[i];
    cin >> path;
    vector<int> q{0, 1, 2, 3};
    int res = 0;
    for (int i = 0; i < 24; i ++ )
    {
        if (check(q)) res ++ ;
        next_permutation(q.begin(), q.end());
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}