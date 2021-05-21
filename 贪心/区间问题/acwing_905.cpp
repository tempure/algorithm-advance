#include <iostream>
#include <algorithm>
using namespace std;

/*
按照每个区间的右端点排序，不断维护最右边的端点
下一个区间的左端点如果大于当前最右，答案+1
*/

const int N = 1e5 + 10;

struct Seg {
    int l, r;
    bool operator<(const Seg & t) {
        return r < t.r;
    }
} segs[N];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        segs[i] = {l, r};
    }
    sort(segs, segs + n);

    int res = 0, ed = -2e9;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (segs[i].l > ed) {
            cnt ++;
            ed = segs[i].r;
        }
    }

    cout << cnt << endl;

    return 0;
}