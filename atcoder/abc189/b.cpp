#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010;
int a[N];

ll n;
long double sum;

ll cnt = 0;

int main() {
    double x;
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        long double a, b;
        cin >> a >> b;
        if (sum +  a * b / 100.0 > x + 1e-8) {
            cout << i << endl;
            break;
        }
        sum +=  a * b / 100.0;
        // cout << sum << endl;
        cnt ++;
    }
    if (cnt == n) printf("-1\n");

    return 0;
}