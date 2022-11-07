#include<bits/stdc++.h>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
int main()
{
    int a, b;
    cin >> a >> b;
    int flag = 0;
    int ans = 0;
    for (int i = 1; i <= 1500; i++)
    {
        if (floor(i * 0.08) == a && floor(i * 0.1) == b)
        {
            ans = i;
            flag = 1;
            break;
        }

    }
    if (flag == 0) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}