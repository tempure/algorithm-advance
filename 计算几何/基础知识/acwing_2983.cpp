#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/*
二分每个玩具所在的区域即可 复杂度O(N*logN)

判断一个点在哪个区域：
如果某点在一个挡板左边，那么挡板下端和该点的连线的向量，和挡板从下而上的向量的叉积为正
如果在挡板右边 那么叉积为负
*/

typedef long long ll;
typedef pair<ll, ll> pll; //点的坐标
const int N = 5010;

int n, m;
pll a[N], b[N]; //每个挡板的上下坐标
int ans[N]; //每个区域内有多少玩具

ll cross(ll x1, ll y1, ll x2, ll y2) { //叉积有向面积
    return x1 * y2 - x2 * y1;
}

ll area(pll a, pll b, pll c) { //计算向量ab和ac的叉积有向面积
    return cross(b.x - a.x,  b.y - a.y, c.x - a.x, c.y - a.y);
}

int find(ll x, ll y) { //二分出该玩具所在的区域
    int l = 0, r = n;
    while (l < r) {
        int mid = l + r >> 1;
        if (area(b[mid], a[mid], {x, y}) > 0) r = mid; //大于0说明在左边
        else l = mid + 1;
    }
    return r;
}

int main() {
    bool is_fisrt = true; //每个样例之间的空格标记 第一个不输出
    while (scanf("%d", &n), n) {
        ll x1, y1, x2, y2;
        scanf("%lld%lld%lld%lld%lld", &m, &x1, &y1, &x2, &y2);
        for (int i = 0; i < n; i++) {
            ll u, l;
            scanf("%lld%lld", &u, &l);
            a[i] = {u, y1}, b[i] = {l, y2};
        }
        a[n] = {x2, y1}, b[n] = {x2, y2};

        if (is_fisrt) is_fisrt = false;
        else puts("");

        memset(ans, 0, sizeof ans);
        while (m --) {
            ll x, y;
            scanf("%lld%lld", &x, &y);
            ans[find(x, y)] ++;
        }
        for (int i = 0; i <= n; i++)
            printf("%d: %d\n", i, ans[i]);
    }
    return 0;
}