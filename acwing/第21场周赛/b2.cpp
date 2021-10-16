#include <bits/stdc++.h>
using namespace std;

//较好的题解：https://www.acwing.com/solution/content/70448/

void solve() {
    string s;
    cin >> s;
    int end = (int)s.size();
    int cnt = 0;
    while (end != 1) {
        cnt++; //operations count
        if (s[end - 1] == '0') end --;
        else {
            for (int i = end - 1; i >= 0; i--) {
                if (s[i] - '0' == 1) s[i] = '0';
                else {
                    s[i] = '1';
                    break;
                }
            }
        }
    }
    if (s[0] == '0') cnt++;
    cout << cnt << endl;
}

int main() {
    solve();
    return 0;
}