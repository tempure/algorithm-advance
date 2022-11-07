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

/*
In mathematics, the Fibonacci numbers, commonly denoted as fn, is a sequence such that each number
is the sum of the two preceding numbers, starting with 1 and 1. That is, f1 = 1, f2 = 1 and
fn = fn−2 + fn−1 (n ≥ 3).
Thus, the beginning of the sequence is 1, 1, 2, 3, 5, 8, 13, 21, . . . .
Given n, please calculate Σ(i=1,n)Σ(j=i+1,n)g(fi, fj), where g(x, y) = 1 when x·y is even, otherwise g(x, y) = 0.
Input
The only line contains one integer n (1 ≤ n ≤ 1e9).
Output
Output one number – Σ(i=1,n)Σ(j=i+1,n)g(fi, fj).

示例1
输入
3
输出
2

示例2
输入
10
输出
24

示例3
输入
100
输出
2739

*/

int n;

int main() {
    cin >> n;
    int cnt = n / 3 * 2;
    cnt += n % 3;
    cout << (ll)(1ll * n * (n - 1) / 2 - 1ll * cnt * (cnt - 1) / 2) << endl;

    return 0;
}