#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//https://www.acwing.com/activity/content/code/content/2575480/
//相当于每个点都有2个出边，BFS求最短路
//一定会有解，可以x2到超过然后减

const int N = 20010;

int n, m;
int q[N], d[N];

int main() {
    cin >> n >> m;

    memset(d, 0x3f, sizeof d);
    d[n] = 0;
    int hh = 0, tt = 0;
    q[0] = n;

    while (hh <= tt) {
        int t = q[hh ++ ];

        int items[] = {t - 1, t * 2};
        for (auto x : items)
            if (x >= 1 && x < N && d[x] > d[t] + 1) {
                d[x] = d[t] + 1;
                q[ ++ tt] = x;
            }
    }

    cout << d[m] << endl;
    return 0;
}