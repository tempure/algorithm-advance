#include<bits/stdc++.h>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;

int main()
{
    int a = 0;
    int b = 0;
    for (int i = 0; i < 3; i++)
    {
        char t;
        cin >> t;
        if (t == 'A') a++;
        else b++;
    }
    if (a == 0 || b == 0) cout << "No" << endl;
    else cout << "Yes" << endl;

    return 0;
}