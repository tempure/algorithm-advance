#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
1.不能成环 也就是走过的不能再走 不然不是最短路
2.不能走到已经走过的相邻的格子旁边的位置 不然不是最短（注意特判反方向走来时候刚经过的格子）
*/

const int N = 210, B = N / 2;

int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool st[N][N];

int get(char c)
{
    if (c == 'U') return 0;
    if (c == 'R') return 1;
    if (c == 'D') return 2;
    return 3;
}

int main()
{
    string str;
    cin >> str;
    bool res = true;

    int x = B, y = B;
    st[x][y] = true;

    for (auto c : str)
    {
        int d = get(c);
        x += dx[d], y += dy[d];
        if (st[x][y]) res = false;

        for (int i = 0; i < 4; i ++ )
            if (i != (d ^ 2) && st[x + dx[i]][y + dy[i]]) //i!=(d^2) 就是特判刚走过来的格子 这个不算 只算三个相邻的
                res = false;

        st[x][y] = true;
    }

    if (res) puts("YES");
    else puts("NO");

    return 0;
}