#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    set<int> S;
    getchar();
    int res = t;
    while (t --) {
        string s;
        getline(cin, s);
        stringstream ssin(s);
        int p = 0;
        while (ssin >> p) {
            if (S.count(p)) res --;
            else S.insert(p);
        }
        // S.insert(temp);
        // cout << temp << endl;
    }
    cout << S.size() << endl;
    return 0;
}