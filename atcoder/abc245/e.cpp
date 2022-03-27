#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc245/editorial/3656
//https://atcoder.jp/contests/abc245/submissions/30437992
//SSRS的代码和题解的顺序交换了，升序降序颠倒 盒子和巧克力也互换一下 本质一样

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    vector<int> B(N);
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }
    vector<int> C(M);
    for (int i = 0; i < M; i++) {
        cin >> C[i];
    }
    vector<int> D(M);
    for (int i = 0; i < M; i++) {
        cin >> D[i];
    }
    vector<tuple<int, int, int>> T;
    for (int i = 0; i < N; i++) {
        T.push_back(make_tuple(A[i], 0, B[i]));
    }
    for (int i = 0; i < M; i++) {
        T.push_back(make_tuple(C[i], 1, D[i]));
    }
    sort(T.begin(), T.end());
    multiset<int> st;
    int cnt = 0;
    for (int i = 0; i < N + M; i++) {
        int t = get<1>(T[i]);
        int x = get<2>(T[i]);
        if (t == 0) {
            st.insert(x);
        }
        if (t == 1) {
            auto itr = st.upper_bound(x);
            if (itr != st.begin()) {
                st.erase(prev(itr));
                cnt++;
            }
        }
    }
    if (cnt == N) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}