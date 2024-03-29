#include <bits/stdc++.h>
using namespace std;

/*
复杂度O(N)的根本原因是最后的回文边界mr是单调递增的
从前往后计算每个位置为中心的回文串半径长度
然后用最右边的边界来更新mid
*/

const int N = 2e7 + 10; //double length of original string

int n;
char a[N], b[N];
int p[N]; //max radius of each mid


void init() {
    int k = 0;
    b[k++] = '$', b[k++] = '#';
    for (int i = 0; i < n; i++) b[k++] = a[i], b[k++] = '#';
    b[k++] = '^';
    n = k;
}

void manacher() {
    int mr = 0, mid;
    for (int i = 1; i < n; i++) {
        if (i < mr) p[i] = min(p[mid * 2 - i], mr - i);
        else p[i] = 1;

        //这个while循环只有在p[i] = mr-i 的情况才会进行更新p[i]
        //如果是p[i] = p[mid * 2 -i],那么直接O(1)计算出p[i],不会在这里while花费复杂度
        //所以整个算法的复杂度可以由内层的while决定，但是这个循环的mr是递增的，mr到字符串结尾的时候算法结束，所以是O(N)
        while (b[i - p[i]] == b[i + p[i]]) p[i]++;
        if (i + p[i] > mr) {
            mr = i + p[i];
            mid = i;
        }
    }
}

void solve() {
    cin >> a;
    n = strlen(a);
    init();
    manacher();
    int res = 0;
    for (int i = 0; i < n; i++) res = max(res, p[i]);
    cout << res - 1 << endl;
}

int main() {
    solve();
    return 0;
}