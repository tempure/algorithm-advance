#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

//https://www.acwing.com/file_system/file/content/whole/index/content/6235964/
/*
这个思路挺厉害的
就所有牌放桌子上，从最底下开始数，第一副牌就是最下面一层，最下面一层N个位置都满了此时第一副牌就好了
然后就跳到第二层开始计算第二副牌的情况，每次新加的牌，看看是哪一摞的，这一摞的高度，最上面一张就是第多少副牌新加的
*/

int delta = 1;
int n, m, t, a[N], f[N];

int main() {
    scanf("%d%d", &n, &m);
    while (m -- ) {
        scanf("%d", &t);
        f[++ a[t]] ++;
        if (f[delta] == n) {
            putchar('1');
            delta ++;
        }
        else putchar('0');
    }
    return 0;
}