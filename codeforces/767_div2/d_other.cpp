#include <bits/stdc++.h>
using namespace std;

set<string> mp, mpl;

bool check(string s) {
    if (s.size() == 1) return 1;
    if (s.front() == s.back()) return 1;
    return 0;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        mp.clear(), mpl.clear();
        bool flg = 0;
        FOR(i, 1, n) {
            string s; cin >> s;
            if (check(s)) flg = 1;
            string ss = s; reverse(ss.begin(), ss.end());
            if (mp.count(ss)) flg = 1;
            if (mpl.count(ss)) flg = 1;
            ss.pop_back();
            if (mp.count(ss)) flg = 1;

            mp.insert(s);
            if (s.size() == 3) s.pop_back(), mpl.insert(s);
        }
        if (flg) print("YES");
        else print("NO");
    }
    return output(), 0;
}
