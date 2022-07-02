#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010;

int n;
int p[N], c[N];


//root 必须第一次染色最优
//子节点和父节点最终颜色不一样必然要染色一次
//子节点和父节点颜色一样就必然不染色，因为如果一样的话，染父节点的时候，把所有子树都已经染成相同的了

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i ++ ) scanf("%d", &p[i]);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &c[i]);

    int res = 1;
    for (int i = 2; i <= n; i ++ )
        if (c[i] != c[p[i]])
            res ++ ;

    printf("%d\n", res);
    return 0;
}