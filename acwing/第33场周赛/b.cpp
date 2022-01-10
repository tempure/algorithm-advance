#include <bits/stdc++.h>
using namespace std;

//最长合法括号子序列
//右括号 能选则选，因为左括号始终满足数量>=右括号

int main() {
    string s;
    cin >> s;
    int l = 0, r = 0 ;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') l++;
        else if (l > 0) {
            l --;
            r++;
        }
    }
    cout << 2 * r << endl;

    return 0;
}
