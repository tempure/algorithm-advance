#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//https://www.cnblogs.com/Kanoon/p/12635169.html

int main()
{
    ll n; cin >> n;

    set<ll> st;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ll t = n;
            while (t % i == 0) t /= i;
            if (t % i == 1) st.insert(i);
        }
    }
    for (ll i = 1; i * i <= n - 1; i++) {
        if ((n - 1) % i == 0) {
            st.insert(i);
            st.insert((n - 1) / i);
        }
    }
    st.erase(1);
    st.insert(n); // k = n 肯定是一个合法解

    cout << st.size() << "\n";

    return 0;
}