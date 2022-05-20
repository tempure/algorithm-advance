#include<bits/stdc++.h>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
int main()
{
    ll n, a, b;
    cin >> n >> a >> b;
    ll t = a + b;
    ll time = n / t;
    ll y = n % t;
    ll sum = 0;
    sum += time * a;
    if (y <= a) sum += y;
    else sum += a;
    cout << sum << endl;

    return 0;
}