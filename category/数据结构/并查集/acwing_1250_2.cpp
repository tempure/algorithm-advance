#include <iostream>
using namespace std;

const int N = 210, M = N * N;
int n, m;
int p[M];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

//特殊的二维坐标隐射一维的技巧
//但是必须坐标x,y都得是从0开始，比较方便
//如果坐标从1开始,那么有个坑，就是这样映射后，一维得到的结果都是从 n+1开始的，所以并查集的p数组的初始化以及
//数组的初始化大小都至少要多初始化n个才行，比较麻烦
int get(int x, int y) {
    return x * n + y;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n * n; i++) p[i] = i;

    int res = 0;
    for (int i = 1; i <= m; i++) {
        int x, y;
        char d;
        cin >> x >> y >> d;
        x --, y --; //转换为从0开始的坐标
        int a = get(x, y);
        int b;
        if (d == 'D') b = get(x + 1, y);
        else b = get(x, y + 1);

        int pa = find(a), pb = find(b);
        if (pa == pb) {
            res = i;
            break;
        }
        p[pa] = pb;
    }
    if (!res) puts("draw");
    else cout << res << endl;

    return 0;
}