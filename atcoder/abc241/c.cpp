#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < n; ++i)

//嗯模拟一下就行了。。。
//https://atcoder.jp/contests/abc241/editorial/3479

int main(void) {
    int n, cnt;
    bool ans = false;
    vector<string>a;
    string str;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str;
        a.push_back(str);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + 5) < n) {
                cnt = 0;
                for (int k = 0; k < 6; k++)if (a[i + k][j] == '#')cnt++;
                if (cnt >= 4)ans = true;
            }
            if ((j + 5) < n) {
                cnt = 0;
                for (int k = 0; k < 6; k++)if (a[i][j + k] == '#')cnt++;
                if (cnt >= 4)ans = true;
            }
            if (((i + 5) < n) && ((j + 5) < n)) {
                cnt = 0;
                for (int k = 0; k < 6; k++)if (a[i + k][j + k] == '#')cnt++;
                if (cnt >= 4)ans = true;
            }
            if ((0 <= (i - 5)) && ((j + 5) < n)) {
                cnt = 0;
                for (int k = 0; k < 6; k++)if (a[i - k][j + k] == '#')cnt++;
                if (cnt >= 4)ans = true;
            }
        }
    }

    if (ans)cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}