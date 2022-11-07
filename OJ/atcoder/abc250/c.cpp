#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
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
//
//存一下下标就行了

void solve() {
	int N;
	cin>>N;

	vector<int> val(N+1),pos(N+1);
	for(int i=1;i<=N;i++)val[i] = i,pos[i] = i;

	int Q;
	cin>>Q;

	vector<int> x(Q);
	for(int i=0;i<Q;i++)cin>>x[i];

	for(int i=0;i<Q;i++){
		int p0 = pos[x[i]];
		int p1 = p0;
		if(p0!=N)p1++;
		else p1--;
		int v0 = val[p0];
		int v1 = val[p1];
		swap(val[p0],val[p1]);
		swap(pos[v0],pos[v1]);
	}

	for(int i=1;i<=N;i++){
		if(i!=1)cout<<' ';
		cout<<val[i];
	}
	cout<<endl;

}

int main() {
	int t = 1;
	// cin >> t;
	while (t --) solve();
	return 0;
}
