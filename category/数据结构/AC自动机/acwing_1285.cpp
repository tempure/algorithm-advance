#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head


//注意这题的题意是每个单词在所有单词出现的次数 不是一个长串进行匹配

/*
    一个单词如果不是其他单词的字串 那么就是一次
    如果是其他串的子串，那就统计后缀
    总共的次数就是 所有的 “前缀的后缀就是原串”的后缀总数 + 原来串
    计算方法:逆向来算,对于每个后缀 求出与之对应的前缀 也就是ne数组处理
    ne[i], ne[ne[i]], ne[ne[ne[i]]]....这样就会处理一个串的所有 与后缀匹配的前缀

    假设f[i]表示i结尾的单词的出现的次数 那直接把f[i]加到f[ne[i]]上去
    因为单词都是在trie的树根连接的 也就是trie的前缀，一个后缀出现了n次，与之对应的前缀就出现了n次
    与后缀匹配的前缀在ne数组已经预处理好了，由fail指针的定义，i向ne[i]连边，图中不会出现环
    直接按照拓扑序从下往上树根处递推，最后枚举一下所有单词，也就是和树根连接的这些，求和即可
*/

const int N = 1000010;

int n;
int tr[N][26], idx;
int f[N]; //每个单词出现的次数
int q[N], ne[N];
char str[N];
int id[210]; //每个单词对应的节点下标

void insert(int x) {
    int p = 0;
    for (int i = 0; str[i] ; i++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
        f[p] ++; //这里统计的是前缀而不是每个单词的结尾，因为单词会出现 其他单词中 每个字母都算
    }
    id[x] = p; //这里id记录的是每个单词结尾的节点号
}

void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i++)
        if (tr[0][i]) q[++tt] = tr[0][i];

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int &p = tr[t][i];
            if (!p) p = tr[ne[t]][i];
            else {
                ne[p] = tr[ne[t]][i];
                q[++tt] = p;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(i);
    }

    build();

    //从树底部网上拓扑序遍历 那么bfs的倒序就是拓扑序
    for (int i = idx - 1; i >= 0; i--) f[ne[q[i]]] += f[q[i]];

    for (int i = 0; i < n; i++) printf("%d\n", f[id[i]]);

    return 0;
}