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

int n;
const int N = 2e5 + 10;
int p[N], s[N];

/*
题意有点费解，就是给定一个置换的规律，初始数组是有序的1,2,3...n排列
每次都按照给定的那个置换进行轮换，求每个数多少次可以置换回自己

仔细观察发现每个数在置换的过程中轨迹都是一个简答环，且这些环中不会有相同的元素
如果初始p[i]=i 那么在图中就是一个孤立点
只需要求出每个点所在简单环的大小即可，由于是简单环，可以直接用维护size的并查集
*/

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T ; cin >> T;
    while (T --) {
        cin >> n;
        for (int i = 1; i <= n; i++) p[i] = i, s[i] = 1;
        for (int i =  1; i <= n; i++) {
            int j;
            cin >> j;
            if (find(i) != find(j)) {
                s[find(j)] += s[find(i)];
                p[find(i)] = find(j);
            }
        }
        for (int i = 1; i <= n; i++)
            cout << s[find(i)] << ' ';
        cout << endl;
    }

    return 0;
}