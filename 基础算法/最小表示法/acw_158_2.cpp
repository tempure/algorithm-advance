#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;
int n;
char a[N], b[N];

int get_min(char s[]) {
    int i = 0, j = 1; //j is latter than i pointer
    while (i < n && j < n) {
        int k = 0;
        while (k < n && s[i + k] == s[j + k]) k++;
        if (k == n) break;
        if (s[k + i] > s[j + k]) i += k + 1;
        else j += k + 1;
        /*
        考虑i + k + 1 == j || j + k + 1 == i
        此时两指针重合，后面所有都会误判，所以要让j+1保持两指针不能重合
        */
        if (i == j) j++; //avoid misjudge
    }
    int pos = min(i, j); //较小的开头位置
    s[n + pos] = 0; //截断
    return pos;
}

void solve() {
    cin >> a >> b;
    n = strlen(a);
    memcpy(a + n, a, n);
    memcpy(b + n, b, n);
    int x = get_min(a), y = get_min(b);
    if (strcmp(a + x, b + y)) puts("No");
    else puts("Yes"), puts(a + x);
}

int main() {
    solve();
    return 0;
}