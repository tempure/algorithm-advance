#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
这个题还是有一些思维难度的，首先要理解操作的顺序对最终的结果无影响。
所以先考虑第二种操作，最后再统一做第一种操作。可以先第一种操作吗？当然可以，但是算法就变了，思路也变了，我不会。
第二点就是要清楚连着两次第二种操作，就等价于做2次第一种操作，所以我们在做第二种操作只需要做一次。
第三点就是要思考每个奇数元素只和后面的一个元素做第2种操作，始终维护前面的序列都为偶数。
第三点的证明也简单，因为假设要操作当前元素和前面一个元素，前面一个元素就会变为奇数，那么此时你为了维护偶数，可以：
- 1.对前面的元素再和当前元素来一次操作2，但是这种操作等价于做两次操作1，所以不考虑
- 2.继续把锅往前推，一直推到第一个元素没法推了，失败。
所以我们第2种操作只能对于当前数和后面的数进行操作减1
*/

const int N = 200010;

int n;
int w[N];

bool check() {
    for (int i = 0; i < n - 1; i ++ )
        if (w[i] % 2)
            w[i] --, w[i + 1] -- ;

    for (int i = 0; i < n; i ++ )
        if (w[i] < 0 || w[i] % 2)
            return false;

    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
        scanf("%d", &w[i]);

    if (check()) puts("YES");
    else puts("NO");

    return 0;
}