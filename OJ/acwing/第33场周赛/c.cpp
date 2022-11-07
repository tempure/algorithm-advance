#include <bits/stdc++.h>
using namespace std;

//https://www.acwing.com/video/3659/
//判断后缀 == 翻转判断前缀
//字符串排序后，如果a是b的前缀，a一定排在b相邻的前面

void solve() {
    unordered_map<string, vector<string> > S;
    int n;
    cin >> n;
    while (n --) {
        string name;
        int cnt;
        cin >> name >> cnt;
        while (cnt --) {
            string number;
            cin >> number;
            reverse(number.begin(), number.end()); //reverse
            S[name].push_back(number);
        }
    }
    cout << S.size() << endl;
    for (auto& [name, ns] : S) { //cpp 17 or later
        sort(ns.begin(), ns.end());
        vector<string> res;
        for (int i = 0; i < ns.size(); i++) {
            //当前字符串和后面的持续比较，可能存在连续接力的前缀属于关系
            if (i + 1 < ns.size() && ns[i + 1].find(ns[i]) == 0) continue;
            res.push_back(ns[i]);
        }

        cout << name << ' ' << res.size();
        for (auto &s : res) {
            reverse(s.begin(), s.end());
            cout << ' ' << s;
        }
        cout << endl;
    }
}

int main() {
    solve();
    return 0;
}
