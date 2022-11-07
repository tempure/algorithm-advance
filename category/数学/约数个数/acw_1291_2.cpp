#include <iostream>
using namespace std;

/*
[1,N]中能整除p的数的个数有N/P下取整个
*/

const int N = 1e6 + 10, M = 1e5 + 10;
int a[M], s[N], cnt[N];
int n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for (int i = 1; i < N; i++)
        for (int j = i; j <= N; j += i)
            s[j] += cnt[i];
    for (int i = 0; i < n; i++) printf("%d\n",  s[a[i]] - 1); //减去自己本身
}

int main() {
    solve();
}