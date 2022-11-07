#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define N 200010
int n, a[N], b[N];

//https://atcoder.jp/contests/abc178/editorial/128
//贪心解法 复杂度不太会证。。。。题解说是O(N)

int main() {
    cin >> n;
    rep(i, n)cin >> a[i];
    rep(i, n)cin >> b[i];
    int j = 0, bef = -1;
    rep(i, n) {
        if (bef != a[i])j = 0; //如果a[i]==a[i-1],那么就不需要重复遍历寻找a[i-1]前面那些b[j]了，直接后面开始找
        if (a[i] == b[i]) {
            for (; j < n; j++) {
                if (a[j] != a[i] && b[j] != a[i]) {
                    swap(b[i], b[j]);
                    break;
                }
            }
            if (a[i] == b[i]) {
                cout << "No\n";
                return 0;
            }
        }
        bef = a[i];
    }
    cout << "Yes\n";
    rep(i, n) {
        if (i)cout << " ";
        cout << b[i];
    }
    cout << "\n";
}