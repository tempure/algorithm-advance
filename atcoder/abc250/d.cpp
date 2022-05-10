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

//https://atcoder.jp/contests/abc250/editorial/3937
//筛质数 O(P)

#define MAXP 1000005
vector<long long> prime_list;
void construct_plist(){
	vector<bool> fl(MAXP,false);
	for(int i=2;i<MAXP;i++){
		if(fl[i]){continue;}
		prime_list.push_back(i);
		for(int j=i;j<MAXP;j+=i){fl[j]=true;}
	}
}
long long f(long long p,long long q){
	double est=1;
	est=(q*q*q);
	est*=p;
	if(est>4e18){return 4e18;}
	return p*q*q*q;
}

void solve() {
	construct_plist();
	long long n;
	cin >> n;
	long long res=0;
	int sz=prime_list.size();
	int q=sz-1;
	for(int p=0;p<sz;p++){
		while(p<q && f(prime_list[p],prime_list[q])>n){q--;}
		if(p>=q){break;}
		res+=(q-p);
	}
	cout << res << '\n';
}

int main() {
	int t = 1;
	// cin >> t;
	while (t --) solve();
	return 0;
}
