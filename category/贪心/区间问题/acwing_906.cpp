#include <iostream>
#include <algorithm>
using namespace std;

//题解：https://www.acwing.com/solution/content/8902/

/*
区间最大厚度问题，也就是活动安排问题/区间分组问题

有若干个活动，第i个活动开始时间和结束时间是[Si,fi]，
同一个教室安排的活动之间不能交叠，求要安排所有活动，少需要几个教室？

将所有的开始时间和结束时间全部加入一个数组然后排序
遇到开始时间就把需要的教室加1，遇到结束时间就把需要的教室减1,在一系列需要的教室个数变化的过程中，
峰值就是多同时进行的活动数，也是我们至少需要的教室数。

错误做法: 区间合并然后寻找合并后不同分隔的大段中区间数量的最大值
这样错的原因是一个大的区间，包含了若干小的区间，但是这些小的区间并没有交集，所以会多算
*/

const int N = 1e5 + 10;
int s[N * 2];
int idx;

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        s[idx++] = l * 2;
        s[idx++] = r * 2 + 1;
    }
    sort(s, s + idx);

    int t = 0, res = 0;
    for (int i = 0; i < idx; i++) {
        if (s[i] & 1) t--;
        else t++;
        res = max(res, t);
    }

    cout << res << endl;

    return 0;
}