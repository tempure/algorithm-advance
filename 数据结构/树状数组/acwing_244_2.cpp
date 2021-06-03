#include <iostream>
using namespace std;

/*
从后往遍历A[i]，边遍历边删高度，A[i]意味着还没被删掉的高度中当前位置的牛是第A[i]小的
本质问题就是求剩余数中第k小的问题
初始将1~n都插入树状数组，每次都二分出树状数组中前缀和为A[i]+1的下标就是当前牛的高度
*/
const int N = 1e5 + 10;
int a[N], tr[N];
int ans[N];
int n;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main() {
    cin >> n;
    for (int i = 2; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) add(i, 1);

    for (int i = n; i >= 1; i --) {
        int k = a[i] + 1;
        int l = 1, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (sum(mid) >= k) r = mid;
            else l = mid + 1;
        }
        ans[i] = r;
        add(r, -1);
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << endl;

    return 0;
}