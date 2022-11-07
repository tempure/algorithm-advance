#include <bits/stdc++.h>
using namespace std;

//倍增实现SA 复杂度O(N*logN)

/*
后缀字符长度不够的位置用空代替，空比任何字符都小
使用倍增的思想，假设此时已经将前k个字符作为关键字排序了所有后缀，那么下次就将前k个字符作为第一关键字
后k个字符作为第二关键字排序，这样只需要log(N)轮就可以排序所有后缀
这里用到一个技巧，就是将前k个已经用过的字符离散化，用一个整数来代替，作为下一次排序的第一关键字
每轮排序的时候，都是使用基数排序，而且是双关键字的基数排序。
具体的操作方法是：先将当前所有后缀按照第二关键字排序，也就是后k个字符，注意遍历的时候要从后往前遍历
这样遍历才能保证排序是稳定的，接着将所有后缀按照第一关键字排序即可

每轮排序O(N)，一共log(N)轮，总复杂度O(N*log(N))
*/
const int N = 1000010;

int n, m;
char s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];

void get_sa() {
    for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1]; //统计小于每个关键字的元素有多少个
    for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;//从后往前依次确定每个元素的排名 统计一个减一个

    //log(N)轮基数排序
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        //将所有后缀按照第二关键字排序
        //最后k个字符，没有第二关键字，最小所以先存下来
        for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k;
        //再按照第一关键字排序
        for (int i = 1; i <= m; i ++ ) c[i] = 0;
        for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
        //将当前所有后缀的前2k个字符离散化
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i ++ )
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
        if (num == n) break;
        m = num;
    }
}

void get_height() {
    for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i ++ ) {
        if (rk[i] == 1) continue;
        if (k) k -- ;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
        height[rk[i]] = k;
    }
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1), m = 122;
    get_sa();
    get_height();
    for (int i = 1; i <= n; i ++ ) printf("%d ", sa[i]);
    puts("");
    for (int i = 1; i <= n; i ++ ) printf("%d ", height[i]);
    puts("");
    return 0;
}