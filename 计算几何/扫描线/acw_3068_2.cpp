/*
N^logN 排序+区间合并，排序后每个区间都暴力扫一次所有矩形判断是否和当前区间有交集

注意合并的时候不存在一个矩形的半个头卡在当前区间的情况，因为要按照所有矩形的头和尾来划分区间
*/

#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using pii = pair<int, int>;
using ll = long long;

const int N = 1010;
int n;
pii l[N], r[N];
pii q[N];

ll range_area(int a, int b) {
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (l[i].x <= a && r[i].x >= b)
            q[cnt++] = {l[i].y, r[i].y};
    if (!cnt) return 0;
    sort(q, q + cnt); //interval first key sort

    ll res = 0;
    int st = q[0].x, ed = q[0].y;
    //merge
    for (int i = 1; i < cnt; i++)
        if (q[i].x <= ed) ed = max(ed, q[i].y);
        else {
            res += ed - st;
            st = q[i].x, ed = q[i].y;
        }
    res += ed - st;
    return res * (b - a);
}

void solve() {
    cin >> n;
    vector<int> xs;
    for (int i = 0; i < n; i++) {
        cin >> l[i].x >> l[i].y >> r[i].x >> r[i].y;
        xs.push_back(l[i].x), xs.push_back(r[i].x);
    }
    sort(xs.begin(), xs.end());
    ll res = 0;
    for (int i = 0; i + 1 < (int)xs.size(); i++) {
        if (xs[i] != xs[i + 1])
            res += range_area(xs[i], xs[i + 1]);
    }
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}