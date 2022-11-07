#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define endl '\n'
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

pq<int, vector<int>, greater<int>> q;

void solve() {
    int a, b, c, d;
    char c1, c2, c3;
    cin >> a >> b >> c >> d;
    bool flag = false;
    if (a == 0 || b == 0 || c == 0 || d == 0) flag = true;
    q.push(a);
    q.push(b);
    q.push(c);
    q.push(d);
    cin >> c1 >> c2 >> c3;
    set<char> S;
    S.insert(c1);
    S.insert(c2);
    S.insert(c3);
    if (S.count('*') && flag) {
        cout << 0 << endl;
        return;
    }
    else {
        char op[3] = {c1, c2, c3};
        int cnt = 0;
        while (sz(q) > 1) {
            auto t1 = q.top();
            q.pop();
            auto t2 = q.top();
            q.pop();
            if ((t1 == 1 || t2 == 1) && op[cnt] == '+') {
                if (sz(q)) {
                    auto t3 = q.top();
                    q.pop();
                    q.push(t3 + min(t1, t2));
                    cnt++;
                    continue;
                }
            }
            if (op[cnt] == '+') q.push(t1 + t2);
            else q.push(t1 * t2);
            cnt++;
            // if(cnt == 3)  break;
        }
    }
    cout << q.top() << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}