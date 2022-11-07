#include <iostream>
#include <cstring>
using namespace std;

const int N = 10010, S = 55;
const int M = 1e6 + 10;

int n, tr[N * S][26];
char str[M]; //mother string
int cnt[N * S];
int q[N * S]; //bfs queue
int ne[N * S]; //fail pointer
int idx;

void insert() {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
    }
    cnt[p]++;
}

void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i++)
        if (tr[0][i]) q[++tt] = tr[0][i];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int c = tr[t][i];
            if (!c) tr[t][i] = tr[ne[t]][i]; //trie 图优化，类似路径压缩的思想
            else {
                ne[c] = tr[ne[t]][i];
                q[++tt] = c;
            }
        }
    }
}

int main() {
    int T;
    cin >> T;

    while (T --) {
        memset(tr, 0, sizeof str);
        idx = 0;
        memset(cnt, 0, sizeof cnt);
        memset(ne, 0, sizeof ne);

        cin >> n;
        while (n --) {
            cin >> str; //复用
            insert();
        }

        build();

        cin >> str; //母串
        int res = 0;
        for (int i = 0, j = 0; str[i]; i++) {
            int t = str[i] - 'a';
            j = tr[j][t];
            int p = j;
            while (p) {
                res += cnt[p];
                cnt[p] = 0; //防止重复计算，比如hsese/hse两个子串的后缀se,会加2次se
                p = ne[p];
            }
        }
        cout << res << endl;
    }
    return 0;
}