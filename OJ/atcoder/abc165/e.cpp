#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
const int N = 1e6 + 1;
int n, m;
int a[N], b[N];

//谜语构造题
//题意很迷不太懂.jpg
//https://atcoder.jp/contests/abc165/submissions/12599546

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    if (n % 2 == 0) {
        int l = 1, r = n / 2;
        int p = 0;
        while (l < r) {
            //  cout << l << ' ' <<r  << endl;
            ++p;
            a[p] = l; b[p] = r;
            l++; r--;
        }
        l = n / 2 + 1; r = n - 1;
        while (l < r) {
            ++p;
            a[p] = l; b[p] = r;
            l++; r--;
        }
    }
    else {
        for (int i = 1; i <= n / 2 ; i++) {
            a[i] = i; b[i] = n - i + 1;
        }
    }
    cin >> m;
    for (int i = 1; i <= m ; i++) cout << a[i] << ' ' << b[i] << '\n';
}