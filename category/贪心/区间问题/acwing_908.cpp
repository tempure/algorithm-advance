#include <iostream>
#include <algorithm>
using namespace std;

//最大不相交区间数量
//右端点排序 统计不相交区间计数即可

const int N = 1e5 + 10;

struct Seg {
    int l, r;
    bool operator <(const Seg & t) {
        return r < t.r;
    }
} seg[N];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        seg[i] = {l, r};
    }
    sort(seg, seg + n);

    int ed = -2e9;
    int cnt = 0;
    for (int i = 0 ; i < n; i++) {
        if (seg[i].l > ed) {
            cnt ++;
            ed = seg[i].r;
        }
    }

    cout << cnt << endl;

    return 0;
}