#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int dp[1000010];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int c;
        cin >> c;
        for (int j = m; j >= c; j--)
        {
            dp[j] = max(dp[j], dp[j - c] + c);
        }
    }
    cout << dp[m] << endl;
    return 0;
}
