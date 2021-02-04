#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100010; //离散化之后的个数

int n, m;
int s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];
int u[N], d[N];
ll ans[N];

/*
所有的子串就是所有后缀的“所有前缀”
对于一个静态的查询，SA排序之后考虑sa[i]和sa[i-1]的后缀，sa[i]中新的前缀的个数，就是后缀i的长度减去height[i]
所以累加所有的len[i] - height[i]即可

但是对于动态在线的问题，需要考虑动态维护height[]和sa[], 考虑到如果在当前字符串的末尾插入一个字符
那么所有的后缀都会被改变，很难维护。
做法:逆序存储字符串，然后每次在开头插入，这样删除开头的一个字符，不会影响后边的后缀
所以直接将所有插入的字符一次性全部插入，然后离线删除每一个字符，同时维护sa[],height[]

对于sa[]的维护使用双链表维护顺序，删除O(1)
维护height[]，每次删除后缀sa[i],那么sa[i+1]会被影响, 因为height[i]是和前一个后缀的lcp
所以删去sa[i]后缀后，更新为和sa[i-1]的lcp即可

此题的x最大1e9 需要离散化
*/

int get(int x) {
    static unordered_map<int, int> hash;
    if (hash.count(x) == 0) hash[x] = ++m;
    return hash[x];
}

void get_sa() {
    for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k;
        for (int i = 1; i <= m; i ++ ) c[i] = 0;
        for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
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
    scanf("%d", &n);
    //逆序读入 然后离散化
    for (int i = n; i; i--) scanf("%d", &s[i]), s[i] = get(s[i]);

    get_sa();
    get_height();

    ll res = 0;
    for (int i = 1; i <= n; i++) {
        res += n - sa[i] + 1 - height[i]; //先加上所有操作之后的结果，然后再逐个减去
        u[i] = i - 1, d[i] = i + 1; //双链表 维护排序之后的后缀
    }
    d[0] = 1, u[n + 1] = n;

    for (int i = 1; i <= n; i++) {
        ans[i] = res; //答案逆序存储
        int k = rk[i], j = d[k]; //k是删去的后缀i, j是i排名后一位的后缀

        //删掉i会影响排名i和i+1的lcp，此时排名i+1的后缀应该更新为和i-1的lcp
        res -= n - sa[k] + 1 - height[k]; //后缀的长度减去height就是新的前缀的数量
        res -= n - sa[j] + 1 - height[j]; //减去i和j之后，重新计算之后再加上
        height[j] = min(height[j], height[k]); //更新lcp
        res += n - sa[j] + 1 - height[j];
        d[u[k]] = d[k], u[d[k]] = u[k]; //链表删除
    }

    for (int i = n; i; i--) printf("%lld\n", ans[i]); //逆序输出答案

    return 0;
}