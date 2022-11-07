#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc185/submissions/18733380
//https://atcoder.jp/contests/abc185/editorial/447

template <typename T>
struct binary_indexed_tree {
    int N;
    vector<T> BIT;
    binary_indexed_tree(int n) {
        N = 1;
        while (N < n) {
            N *= 2;
        }
        BIT = vector<T>(N + 1, 0);
    }
    void add(int i, T x) {
        i++;
        while (i <= N) {
            BIT[i] ^= x;
            i += i & -i;
        }
    }
    T sum(int i) {
        T ans = 0;
        while (i > 0) {
            ans ^= BIT[i];
            i -= i & -i;
        }
        return ans;
    }
    T query(int L, int R) {
        return sum(R) ^ sum(L); //修改此处模板
    }
};

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    binary_indexed_tree<int> BIT(N);
    for (int i = 0; i < N; i++) {
        BIT.add(i, A[i]);
    }
    for (int i = 0; i < Q; i++) {
        int T, X, Y;
        cin >> T >> X >> Y;
        if (T == 1) {
            X--;
            BIT.add(X, Y);
        }
        if (T == 2) {
            X--;
            cout << BIT.query(X, Y) << endl;
        }
    }
    return 0;
}