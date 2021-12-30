#include <bits/stdc++.h>
using namespace std;

//https://www.acwing.com/video/3620/

void solve() {
    string s;
    cin >> s;
    stack<int> stk;

    int resl = 0, resc = 1; //最长答案 以及答案的数量
    for (int i = 0; s[i]; i++) {
        if (stk.size() && s[i] == ')' && s[stk.top()] == '(') stk.pop();
        else stk.push(i);

        int r;
        if (stk.size()) r = i - stk.top();
        else r = i + 1;

        if (r > resl) resl = r, resc = 1;
        else if (r > 0 && r == resl) resc ++ ;
    }
    printf("%d %d\n", resl, resc);
}

int main() {
    solve();
    return 0;
}