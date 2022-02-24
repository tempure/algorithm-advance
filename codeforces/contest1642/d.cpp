#include <bits/stdc++.h>
using namespace std;

//https://codeforces.com/blog/entry/100249
/*
构造思路就是题解所说：翻转一个数组的任意前缀任意多次，可以将这个数组排序
证明也很简单，每次都找当前除了排好序那一连串之外元素的最小元素前的位置，然后reverse前缀
。。。可以模拟一下就行了。。。
*/

void reverse_pref(vector<int> &ar, vector<pair<int, int>> &ans,
                  vector<int> &lens, int &mdf, int len) {
    for (int i = 0; i < len; ++i)
        ans.emplace_back(len + mdf + i, ar[i]);
    if (len != 0)
        lens.push_back(len * 2);
    mdf += len * 2;
    reverse(ar.begin(), ar.begin() + len);
}

void move_to_front(vector<int> &ar, vector<pair<int, int>> &ans,
                   vector<int> &lens, int &mdf, int id) {
    reverse_pref(ar, ans, lens, mdf, id);
    reverse_pref(ar, ans, lens, mdf, id + 1);
}

signed IlkrasTEQ1Solve(int n, vector<int> ar) {

    int xr = 0;
    unordered_map<int, int> cnt;
    for (auto &it : ar) {
        cnt[it]++;
    }
    for (auto &it : cnt)
        if (it.second % 2) {
            cout << "-1\n";
            return 0;
        }
    vector<int> br = ar;
    sort(br.rbegin(), br.rend());
    vector<pair<int, int>> ans;
    vector<int> lens;
    ans.reserve(n * n * 2);
    lens.reserve(n * 2);
    int mdf = 0;
    for (int i = 0; i < n; ++i) {
        int fnd = (int)(find(ar.begin() + i, ar.end(), br[i]) - ar.begin());
        move_to_front(ar, ans, lens, mdf, fnd);
    }
    for (int i = 0; i < n; ++i) {
        int lst = i;
        for (; lst < n && ar[lst] == ar[i]; ++lst) {
        }
        lens.push_back(lst - i);
        i = lst - 1;
    }
    cout << (int)ans.size() << "\n";
    for (auto &it : ans)
        cout << it.first << " " << it.second << "\n";
    cout << (int)lens.size() << "\n";
    for (auto &it : lens)
        cout << it << " ";
    cout << "\n";
    return 0;
}

signed main() {
    (*cin.tie(0)).sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        vector<int> ar(n);
        for (auto &it : ar)
            cin >> it;
        IlkrasTEQ1Solve(n, ar);
    }
    return 0;
}