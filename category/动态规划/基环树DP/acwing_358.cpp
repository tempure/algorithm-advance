#include <bits/stdc++.h>
using namespace std;

/*
给出一个基环树森林，求出所有基环树的直径和

由于一棵树只有 一个环，直接用栈存一下即可 没必要用tarjan
拆环复制一遍成链，单调队列求最值即可

注意环上的前缀和，由于边权不是1，所以复制的后一半的每个点前缀和要加上环的总权值和
*/

typedef long long ll;

const int N = 1000010, M = N * 2;

int n;
int h[N], e[M], w[M], ne[M], idx;
int fu[N], fw[N], q[N]; //q单调队列下标
int cir[N],  ed[N], cnt; //cir连续存放所有环的点 ed存每个环在cir中结束的下标
ll s[N], d[N * 2], sum[N * 2]; //d单调队列 s是环的前缀和 sum是复制一遍后的前缀和
bool st[N], ins[N]; //用栈来存每个环 ins点是否在栈中
ll ans; //每颗基环树的直径 最后相加

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dfs_c(int u, int from) {
    st[u] = ins[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        if (i == (from ^ 1)) continue;
        int j = e[i];
        fu[j] = u, fw[j] = w[i];
        if (!st[j]) dfs_c(j, i);
        else if (ins[j]) { //出现环
            cnt ++;
            ed[cnt] = ed[cnt - 1]; //开始更新下一个环
            ll sum = w[i];
            for (int k = u; k != j; k = fu[k]) {
                s[k] = sum;
                sum += fw[k];
                cir[++ed[cnt]] = k;
            }
            s[j] = sum, cir[++ed[cnt]] = j; //环的终点
        }
    }
    ins[u] = false;
}

ll dfs_d(int u) { //求出环上每个点为根的子树的直径
    st[u] = true;
    ll d1 = 0, d2 = 0; //最长和次长路径
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (st[j]) continue;
        ll dist = dfs_d(j) + w[i];
        if (dist >= d1) d2 = d1, d1 = dist;
        else if (dist > d2) d2 = dist;
    }
    ans = max(ans, d1 + d2);
    return d1;
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(i, a, b), add(a, i, b);
    }

    //先搜出所有的环
    for (int i = 1; i <= n; i++)
        if (!st[i])
            dfs_c(i, -1);

    memset(st, 0, sizeof st);

    //将整个森林中所有环标记，在接下来搜树的过程不会搜环上的点
    for (int i = 1; i <= ed[cnt]; i++) st[cir[i]] = true;

    ll res = 0; //最终的答案

    for (int i = 1; i <= cnt; i++) { //遍历所有的环
        ans = 0;
        int sz = 0; //环上点的个数

        //遍历所有环上的点
        for (int j = ed[i - 1] + 1; j <= ed[i]; j++) { //ed[]下标从1开始
            int k = cir[j];
            d[sz] = dfs_d(k);
            sum[sz] = s[k];
            sz ++;
        }
        for (int j = 0; j < sz; j++) //环复制一遍为链
            //这里复制的一部分前缀和要加上整个环的和 因为这里的边权不是1
            d[sz + j] = d[j], sum[sz + j] = sum[j] + sum[sz - 1];

        //单调队列
        int hh = 0, tt = -1;
        for (int j = 0; j < sz * 2; j++) {
            if (hh <= tt && j - q[hh] >= sz) hh++;
            if (hh <= tt) ans = max(ans, d[j] + sum[j] + d[q[hh]] - sum[q[hh]]);
            while (hh <= tt && d[q[tt]] - sum[q[tt]] <= d[j] - sum[j]) tt --;
            q[++tt] = j;
        }
        res += ans;
    }

    printf("%lld\n", res);
    return 0;
}