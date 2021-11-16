#include<bits/stdc++.h>
using namespace std;

using ll = long long;

/*
这题意好费解啊，我英语太拉了

就是问所有7个原点构成的四边形，里面不能存在其他的7，问最多选多少个7


直接极角排序，上边斜率较大的边为第一关键字，然后把斜率当作区间来排序

然后按照大的区间端点排序贪心，经典的最多任务完成数量问题
*/

// p/q
struct fraction {
    ll p, q;
    fraction(ll P = 0, ll Q = 1): p(P), q(Q) {}
    bool operator<(const fraction &other)const {
        return p * other.q < other.p * q;
    }
    bool operator<=(const fraction &other)const {
        return p * other.q <= other.p * q;
    }
};

int main() {
    int N; cin >> N;
    vector<ll> x(N), y(N);
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i];
    vector<pair<fraction, fraction>> data(N);
    for (int i = 0; i < N; i++) data[i] = make_pair(fraction(y[i], x[i] - 1), fraction(y[i] - 1, x[i]));
    sort(data.begin(), data.end());
    int ans = 0;
    fraction now;
    for (auto p : data) {
        if (now <= p.second) {
            ans++;
            now = p.first;
        }
    }
    cout << ans << endl;
}