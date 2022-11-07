#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#define ll long long
#define SIZE 2010
#define rep(i, a, b) for (int i = a; i <= b; ++i)
using namespace std;
void io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
int h, w, k, a[15][SIZE], pre[15][SIZE], ans = 1e9;

//就是很暴力的枚举行，然后枚举列 二维前缀和判断
//https://www.cnblogs.com/st1vdy/p/12554764.html#e---dividing-chocolate

int query(int xa, int ya, int xb, int yb) {
    return pre[xb][yb] - pre[xa][yb] - pre[xb][ya] + pre[xa][ya];
}

void gao(int top) {
    vector<int> vec(1, 0);
    int cnt = 1, tmp = 0, pre = 0;
    while (top) {
        if (top & 1) ++tmp, vec.emplace_back(cnt);
        top >>= 1;
        ++cnt;
    }
    vec.emplace_back(h);

    rep(i, 1, w) {
        bool f = false;
        rep(j, 1, (vec.size() - 1)) {
            if (query(vec[j - 1], pre, vec[j], i) > k) {
                if (query(vec[j - 1], i - 1, vec[j], i) > k) return;
                f = true;
            }
        }
        if (f) { ++tmp; pre = i - 1; }
    }
    ans = min(ans, tmp);
}

int main() {
    io(); cin >> h >> w >> k;
    int top = (1 << (h - 1)) - 1;
    rep(i, 1, h) {
        string s; cin >> s;
        rep(j, 1, w) a[i][j] = s[j - 1] - '0';
    }
    rep(i, 1, h)
    rep(j, 1, w)
    pre[i][j] = a[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
    for (int i = top; i >= 0; --i) gao(i);
    cout << ans;
}
