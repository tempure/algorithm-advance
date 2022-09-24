#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
这个题还是有一些思维难度的，首先要理解操作的顺序对最终的结果无印象
所以先考虑第二种操作，最后再统一做第一种操作。可以先第一种操作吗？当然可以，但是算法就变了，思路也变了，我不会。
第二点就是要清楚连着两次第二种操作，就等价于做2次第一种操作，所以我们在做第二种操作只需要做一次。
第三点就是要思考每个元素只和后面的一个元素做第二种操作，始终维护前面的序列都为偶数。
第三点的证明也简单，就直接看录播视频的讲解就行了。
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