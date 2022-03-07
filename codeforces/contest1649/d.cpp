#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, m, a[N], s[N];

//https://codeforces.com/contest/1649/submission/148568798

bool work() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) s[i] = 0;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    n = unique(a + 1, a + n + 1) - a - 1;
    //cout<<"n="<<n<<endl;
    for (int i = 1; i <= n; i++) s[a[i]]++; //cout<<a[i]<<" "; puts("");
    for (int i = 1; i <= m; i++) s[i] += s[i - 1];
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        for (int j = x; j <= m; j += x) if (s[min(m, j + x - 1)] - s[j - 1] && !(s[j / x] - s[j / x - 1])) return 0;
    }
    return 1;
}
int main()
{
    //srand(time(0));
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    int T; cin >> T;
    while (T--) {
        if (work()) puts("Yes");
        else puts("No");
    }
    return 0;
}
