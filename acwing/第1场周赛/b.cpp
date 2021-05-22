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

#define MAXN 200010

// function to perform query 1
void performQueryOne(int num, int* left, int* right, int* position, int* mark) {
    // count number of elements on left
    *left = *left + 1;

    // store the index number
    position[num] = *(left);

    // mark the element is on left
    mark[num] = 1;
}

// function to perform query 2
void performQueryTwo(int num, int* left, int* right, int* position, int* mark) {
    // count number of elements on right
    *right = *right + 1;

    // store the index number
    position[num] = *(right);

    // mark the element is on right
    mark[num] = 2;
}

// function to perform query 3
int performQueryThree(int num, int* left, int* right, int* position, int* mark) {
    int toright, toleft;

    // if the element is on right
    if (mark[num] == 2) {
        toright = *right - position[num];
        toleft = position[num] - 1 + *left;
    }

    // if the element is on left
    else if (mark[num] == 1) {
        toleft = *left - position[num];
        toright = position[num] - 1 + *right;
    }

    int res = min(toleft, toright);
    return res;
}

// Driver Code
int main() {

    int left = 0, right = 0;

    // hashing arrays
    int position[MAXN] = { 0 };
    int mark[MAXN] = { 0 };

    // int num = 3;
    int t; cin >> t;
    while (t --) {

        char op;
        int num;
        cin >> op >> num;

        // query type-1
        if (op == 'L')
            performQueryOne(num, &left, &right, position, mark);

        // query type-2
        // num = 5;
        else if (op == 'R')
            performQueryTwo(num, &left, &right, position, mark);
        else cout << performQueryThree(num, &left, &right, position, mark) << endl;

        // query type-3
        // num = 3;
        // int res = performQueryThree(num, &left, &right, position, mark);
        // cout << res << endl;
    }

    return 0;
}