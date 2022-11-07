#include <bits/stdc++.h>
using namespace std;
//https://atcoder.jp/contests/abc177/submissions/16321676
//https://atcoder.jp/contests/abc177/editorial/93
//筛法分解质因数 模板里面写过一个倍数法的 O(N*logN) 应该比这个更快。。。
//好久不写数论题了。。。。

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    vector<int> cnt(1000001, 0);
    for (int i = 0; i < N; i++) {
        cnt[A[i]]++;
    }
    bool ok_pair = true;
    for (int i = 2; i <= 1000000; i++) { //直接暴力枚举所有数了，按题解意思只枚举质数的倍数
        int sum = 0;
        for (int j = i; j <= 1000000; j += i) {
            sum += cnt[j]; //i的倍数的个数
        }
        if (sum >= 2) {
            ok_pair = false;
        }
    }
    int g = A[0];
    for (int i = 1; i < N; i++) {
        g = gcd(g, A[i]); //第二个条件直接暴力就行了。。。。
    }
    if (ok_pair) {
        cout << "pairwise coprime" << endl;
    } else if (g == 1) {
        cout << "setwise coprime" << endl;
    } else {
        cout << "not coprime" << endl;
    }
}