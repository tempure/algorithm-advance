//https://codeforces.com/problemset/problem/940/C
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
int n, k;
char s1[N], s2[N];
bool st[26];

char get_min() {
    for (int i = 0; i < 26; i++)
        if (st[i])
            return i + 'a';
    return -1;
}

char get_next(int t) {
    for (int i = t + 1; i < 26; i++)
        if (st[i])
            return i + 'a';
    return -1;
}

void solve() {
    cin >> n >> k;
    cin >> s1;
    memset(st, 0, sizeof st);
    for (int i = 0; i < n; i++) st[s1[i] - 'a'] = true;

    if (k > n) {
        cout << s1;
        char c = get_min();
        for (int i = n; i < k; i++) cout << c;
        puts("");
    }
    else {
        s2[k] = 0; //字符串结尾截断
        for (int i = k - 1; i >= 0; i--) {
            char c = get_next(s1[i] - 'a');
            if (c != -1) {
                s2[i] = c;
                for (int j = 0; j < i; j++) s2[j] = s1[j];
                break;
            }
            s2[i] = get_min();
        }
        puts(s2);
    }
}


int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}
