#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
int a[N];
int n, m;

/*
先排序,增大中位数只能将中间位置中位数以及与中位数相等（如果存在）的一段全部增大才可以
或者如果不存在和中位数相同的一段，要将其变大为另外一个x，那么要将排序后中位数后所有小于x的全部变成x才可以
直接二分x即可
*/

bool check(int mid) {
    ll res = 0;
    for (int i = n / 2; i < n; i++)
        if (a[i] < mid)
            res += mid - a[i];

    return res <= m;
}

int main() {
    cin >> n >> m;
    for (int i = 0 ; i < n; i++) cin >> a[i];

    sort(a, a + n);

    ll l = 1, r = 2e9;

    while (l < r) {
        ll mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    cout << r << endl;

    return 0;
}