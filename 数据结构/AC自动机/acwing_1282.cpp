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

//AC自动机 线性复杂度

const int N = 10010, S = 55;
const int M = 1000010;

int n, tr[N * S][26]; //trie
int cnt[N * S]; //每个节点结尾的单词的数量
char str[M];
int q[N * S]; //bfs宽搜队列
int ne[N * S];
int idx; //trie idx

void insert() {
    int p = 0; //根节点
    for (int i = 0; str[i]; i ++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
    }
    cnt[p] ++;
}

//bfs构建AC自动机

void build() {
    int hh = 0, tt = -1;
    for (int i = 0 ; i < 26; i++) {
        //将根节点的子节点全部入队 就是第一层
        if (tr[0][i]) q[++tt] = tr[0][i];
    }

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int j = ne[t];
            int c = tr[t][i];
            if (!c) continue;
            while (j && !tr[j][i]) j = ne[j];
            //注意对于相同的i,所有节点的子节点i都是相同的字母 因为是按照字母序从小到大的
            if (tr[j][i]) j = tr[j][i];
            ne[c] = j;
            q[++tt] = c;
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T --) {
        memset(tr, 0, sizeof tr);
        idx = 0;
        memset(cnt, 0, sizeof cnt);
        memset(ne, 0, sizeof ne);

        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            insert();
        }

        build();

        scanf("%s", str); //待匹配的长串
        int res = 0;
        for (int i = 0, j = 0; str[i]; i++) {
            int t = str[i] - 'a';
            //当前已经匹配到了trie中的j节点，如果j的子节点tr[j][t]不存在
            //那就说明根到tr[j][t]这个单词不存在 但是长串和短串此时都有相同的前后缀
            //就直接跳到ne[j] 如果此时的tr[j][t]存在 说明就从根匹配到了一个单词
            while (j && !tr[j][t]) j = ne[j];
            if (tr[j][t]) j = tr[j][t]; //J就是能匹配到str中一个单词，而且是最靠近目前遍历到的str的位置的最接近的尾部
            //j在整个匹配过程中都是一直递增的，注意，也就是说j每次循环结束，都是一个匹配完成的单词的结尾
            //然后等着下一个str[i]来匹配，进行跳转匹配


            //每找到一个单词遍历j的所有fail指针
            //因为j如果能找到，那么跳转到ne[j]的单词也必然存在 就直接顺便加上 题目求的是所有单词出现的总个数
            //如果一个单词多次出现 那么只算cnt[p]次就可以了,也就是最开始insert的次数
            int p = j;
            while (p) {
                res += cnt[p];
                cnt[p] = 0;
                p = ne[p];
            }
        }

        printf("%d\n", res);
    }
    return 0;
}