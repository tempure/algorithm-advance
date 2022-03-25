#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//维护size DSU 即可
//答案就是最大的联通块的 size
//因为最大的连通块里面每个点最少属于一个单独的组

struct UnionFind {
    //If the vertex is a parent, this value will be the number of vertices that belongs to the set, multiplied by -1
    //Otherwise, this value will be the parent's id
    vector<int> r;

    UnionFind(int N) {
        r = vector<int>(N, -1);
    }

    int root(int x) {
        if (r[x] < 0) return x;
        return r[x] = root(r[x]);
    }

    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        if (r[x] > r[y]) swap(x, y);
        r[x] += r[y];
        r[y] = x;
        return true;
    }

    int size(int x) {
        return -r[root(x)];
    }
};


int main() {
    int N, M;
    cin >> N >> M;

    //Make friends-sets
    UnionFind UF(N);
    for (int i = 0; i < M; i++)
    {
        int A, B;
        cin >> A >> B;
        A -= 1; B -= 1;
        UF.unite(A, B);
    }

    //Find the maximum friends-set
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans = max(ans, UF.size(i));
    }

    cout << ans << endl;
}
