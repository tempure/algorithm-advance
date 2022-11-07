#include <bits/stdc++.h>
using namespace std;


//2021 10.8 update 注释

const int N = 1e4 + 10, S = 55;
const int M = 1e6 + 10;

int n, tr[N * S][26];
char str[M];
int cnt[N * S];
int q[N * S];
int ne[N * S];
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
        for (int i =  0; i < 26; i++) {
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
    memset(tr, 0, sizeof tr);
    memset(cnt, 0, sizeof cnt);
    memset(ne, 0, sizeof ne);
    idx = 0;

    cin >> n;
    while (n --) {
        cin >> str;
        insert();
    }
    build();

    cin >> str;
    int res = 0;

    for (int i = 0, j = 0; str[i]; i++) {
        int t = str[i] - 'a';
        j = tr[j][t]; //注意j在整个for循环中是一直在匹配字符串，如果tr[j][t]==0,说明当前位置往下走匹配不到了，就重新回到root 0号点重新开始匹配
        int p = j;
        while (p) {
            //如果当前节点的单词出现过，fail指针所指向的单词是当前单词的后缀，那也要看看是不是这个后缀cnt是多少，后缀是不是一个单词
            res += cnt[p];
            cnt[p] = 0; //防止一个 fail 指针指向的单词后缀被多个有这个后缀的长的单词加
            //比如 sheee hee 都有ee，而且ee是一个存在的单词，那么ee应该只被加一次，因为问的是有多少个单词出现，每个单词只需要算一次
            p = ne[p];
        }
    }
    cout << res << '\n';
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}