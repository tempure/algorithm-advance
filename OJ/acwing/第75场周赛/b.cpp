#pragma GCC optimize("O2")
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
#define watch(x) cerr << (#x) << " is " << (x) << endl
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

map<int, string> mp;
vector<pair<int,int> > a;

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string name, role;
        cin >> name >> role;
        int p = 0;
        if(role == "rat") p = 1;
        else if(role == "woman" || role == "child") p = 2;
        else if(role == "man") p = 3;
        else p = 4;

        mp[i]= name;
        a.push_back({p, i});
    } 
    sort(all(a));
    for(auto t : a){
        cout << mp[t.second] << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}