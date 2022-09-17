#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
这题题意有点模糊，就是求要再至少打掉多少个格子，才能最多放 a-1 艘战舰
就在当前已经被打的格子分割的段中，每段中可以放一些战舰
然后在这些可以这些可以放战舰的小段中，每段最后打一发就行了
*/

const int N = 200010;

int n, a, b, k;
char s[N];

int main() {
    scanf("%d%d%d%d", &n, &a, &b, &k);
    scanf("%s", s + 1);

    int res = 0;
    for (int i = 1, len = 0; i <= n; i ++ )
        if (s[i] == '1') len = 0;
        else {
            if ( ++ len == b) {
                len = 0;
                res ++ ;
            }
        }

    res -= a - 1;
    printf("%d\n", res);
    for (int i = 1, len = 0; res; i ++ )
        if (s[i] == '1') len = 0;
        else {
            if ( ++ len == b) {
                printf("%d ", i);
                res -- ;
                len = 0;
            }
        }

    return 0;
}