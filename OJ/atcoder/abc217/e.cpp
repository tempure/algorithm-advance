#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

/*
同时维护multiset和 一个queue
如果插入直接 queue push就好
查询最小，如果set有元素之间输出set最小值，然后从set中删去
排序：直接把所有queue的元素插入set,然后清空 set

每个元素最多进入set一次，O(n*logn)
*/

multiset<int> s;
queue<int> q;

void solve() {
    int t;
    cin >> t;
    while (t --) {
        int op, x;
        cin >> op;
        if (op == 1) {
            cin >> x;
            q.push(x);
        }
        else if (op == 2) {
            if (sz(s)) {
                auto it = s.begin();
                cout << *it << endl;
                s.erase(it);
            }
            else {
                cout << q.front() << endl;
                q.pop();
            }
        }
        else {
            while (sz(q)) {
                s.insert(q.front());
                q.pop();
            }
        }
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}