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
//head

const int N = 100010, M = 350;

int n, m, len; //len是每个块的长度
ll add[M], sum[M]; //add[]是懒标记 sum[]是块元素的sum
int w[N];

int get(int i) {
    return i / len; //返回每个位置的点所在的块
}

void change(int l, int r, int d) {
    if (get(l) == get(r)) { //特判在同一个块中的情况 直接暴力即可
        for (int i = l; i <= r; i++) {
            w[i] += d;
            sum[get(i)] += d;
        }
    }
    else {
        int i = l, j = r; //先计算左右2段不完整的块 然后计算完整的块
        while (get(i) == get(l)) w[i] += d, sum[get(i)] += d, i++;
        while (get(j) == get(r)) w[j] += d, sum[get(j)] += d, j--;
        for (int k = get(i); k <= get(j); k++) sum[k] += len * d, add[k] += d;
    }
}

ll query(int l, int r) {
    ll res = 0;
    if (get(l) == get(r)) {
        //add[]数组的意义就是为了计算不完整的块 完整的块只需要用到sum[]
        for (int i = l; i <= r; i++) res += w[i] + add[get(i)];
    }
    else {
        int i = l, j = r;
        while (get(i) == get(l)) res += w[i] + add[get(i)], i++;
        while (get(j) == get(r)) res += w[j] + add[get(j)], j--;
        for (int k = get(i); k <= get(j); k++) res += sum[k];
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        sum[get(i)] += w[i];
    }

    char op[2];
    int l, r, d;
    while (m --) {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C') {
            scanf("%d", &d);
            change(l, r, d);
        }
        else printf("%lld\n", query(l, r));
    }

    return 0;
}