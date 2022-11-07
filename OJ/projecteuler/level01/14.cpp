#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000000;
int a[maxn];

//https://blog.csdn.net/error311/article/details/108605672
//记忆化搜索，不暴力

int get(ll x) {         // 此处需要长整型，否则会溢出
    if (x == 1) {
        return 1;
    }
    if (x < maxn && a[x] != 0) { // 如果获取到了当前数字的链长，直接返回就行
        return a[x];
    }
    int k = 0;
    if (x % 2 == 0) {
        k = get(x / 2) + 1;   // 寻找 x/2 的链长  + 1就行
    } else if (x * 3 + 1) {   // 同理
        k = get(x * 3 + 1) + 1;
    }
    if (x < maxn) {
        a[x] = k;       // 只有小于maxn的数才记录，否则没意义（而且数组长度也太大）
    }
    return k;
}
int main() {
    int ans = 1;
    for (int i = 1; i < maxn; i++) {
        a[i] = get(i);
        if (a[i] > a[ans]) {
            ans = i;
        }
    }
    cout << "length :" << a[ans] << endl;
    cout << ans << endl;
    return 0;
}