//最长上升子序列(非连续)


//O(N^2)做法
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1010;

int a[N], f[N]; //以a[i]结尾的最长LIS长度

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        f[i] = 1;  //只有a[i] 一个数的情况
        for (int j = 1; j < i; j++)
            if (a[j] < a[i])
                f[i] = max(f[i], f[j] + 1);
    }

    int res = 0;
    for (int i = 1; i <= n; i++) res = max(res, f[i]);

    cout << res << endl;

    return 0;
}

//二分做法O(N*logN) 贪心 非DP

#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int a[N], q[N]; //a原始序列, q[i]:长度为i的LIS的结尾的最小可能值

//q[i]在二分的同时会维护单调性，严格单调递增 q[]一定不含相同元素

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    int len = 0; //q内的元素个数
    q[0] = 0xcfcfcfcf; //哨兵 去掉也能A 意思是长度为0的LIS的结尾最小可能值不存在
    for (int i = 0; i < n; i++) {
        //二分
        int l = 0, r = len; //注意此处只能l=0,r=len, len-1,len+1都会错，因为q[]内元素实际下标是[1,len]
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (q[mid] < a[i]) l = mid; //不能写成 q[mid] <= a[i] 因为是左侧逼近找比a[i]小的最大元素,而不是找a[i]
            else r = mid - 1;
        }
        len = max(len, r + 1); //a[i]大于所有q[]的元素，那就只能接在结尾
        q[r + 1] = a[i]; //q[r+1]是大于a[i]的，q[r]是小于a[i]的,所以直接更新q[r+1]
    }
    cout << len << endl;

    return 0;
}