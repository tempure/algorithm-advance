#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
CRT的通解是的通解x = x0 + K*M，M是所有模数乘积
所以最小正整数解直接 求出一组解后 mod M 即可
*/

const int N = 11;
int n;
int A[N], B[N];

void exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) x = 1, y = 0;
    else {
        exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}

// x === B[i] mod A[i]
void CRT() {
    cin >> n;
    ll M = 1;
    for (int i =  0; i < n; i++) {
        cin >> A[i] >> B[i];
        M *= A[i];
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll Mi = M / A[i];
        ll ti, y;
        exgcd(Mi, A[i], ti, y);
        res += (B[i] * Mi * ti);
    }
    cout << (res % M + M) % M << endl; //最小正整数解
}

int main() {
    CRT();
    return 0;
}