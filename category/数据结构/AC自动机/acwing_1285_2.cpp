#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e6 + 10;
int tr[N][26], f[N];
int ne[N];
int q[N];
char str[N];
int id[210];
int n, idx;

void insert(int x) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
        f[p]++;
    }
    id[x] = p;
}

void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i++)
        if (tr[0][i]) q[++tt] = tr[0][i];

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int c = tr[t][i];
            if (!c) tr[t][i] = tr[ne[t]][i];
            else {
                ne[c] = tr[ne[t]][i];
                q[++tt] = c;
            }
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str;
        insert(i);
    }
    build();

    for (int i = idx - 1; i >= 0; i --) f[ne[q[i]]] += f[q[i]];
    for (int i = 0; i < n; i++) cout << f[id[i]] << endl;
}

int main() {
    solve();
    return 0;
}