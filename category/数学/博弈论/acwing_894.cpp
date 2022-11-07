#include <bits/stdc++.h>
using namespace std;

/*
拆分NIM博弈，每个状态可以产生两个新的状态
每一堆可以变成不大于原来那堆的任意大小的两堆
相当于一个局面拆分成了两个局面，由SG函数理论，多个独立局面的SG值，等于这些局面SG值的异或和。
*/

const int N = 110;
int f[N];

int sg(int x) {
    if (f[x] != -1) return f[x];

    unordered_set<int> S;

    for (int i = 0; i < x; i++)
        for (int j = 0; j <= i; j++)
            S.insert(sg(i) ^ sg(j));

    for (int i = 0; ; i++)
        if (!S.count(i))
            return f[x] = i;
}

int main() {
    int n;
    cin >> n;

    int res = 0;
    memset(f, - 1, sizeof f);

    while (n --) {
        int x;
        cin >> x;
        res ^= sg(x);
    }

    if (res == 0) puts("No");
    else puts("Yes");

    return 0;
}