#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/*
横向区间排序 排序后处理每一个区间
对于每个区间，纵向排序+区间合并
复杂度O(N^2*logN)

如果达到1e5，就需要扫描线+线段树处理了
*/

typedef long long ll;
typedef pair<int, int> pii;
const int N = 1010;

int n;
pii l[N], r[N]; //左上和右下坐标
pii q[N];

ll range_area(int a, int b) {
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (l[i].x <= a && r[i].x >= b) //该矩形横跨该区间
            q[cnt++] = {l[i].y, r[i].y};
    if (!cnt) return 0;
    sort(q, q + cnt); //纵向排序 + 区间合并

    ll res = 0;
    int st = q[0].x, ed = q[0].y;
    //区间合并
    for (int i = 1; i < cnt; i++)
        if (q[i].x <= ed) ed = max(ed, q[i].y);
        else {
            res += ed - st;
            st = q[i].x, ed = q[i].y;
        }

    res += ed - st; //最后一个区间
    return res * (b - a);
}

int main() {
    scanf("%d", &n);
    vector<int> xs; //所有的横坐标
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &l[i].x, &l[i].y, &r[i].x, &r[i].y);
        xs.push_back(l[i].x), xs.push_back(r[i].x);
    }
    sort(xs.begin(), xs.end());

    ll res = 0;
    for (int i = 0; i + 1 < xs.size(); i++) //枚举所有横向区间
        if (xs[i] != xs[i + 1])
            res += range_area(xs[i], xs[i + 1]);
    printf("%lld\n", res);

    return 0;
}