#include<bits/stdc++.h>
using namespace std ;
#define ll long long
#define db double
#define ld long double
#define IOS  ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#pragma GCC optimize(2)
#define ull unsigned long long
#define maxn 200005
int l[maxn], r[maxn];

//https://blog.csdn.net/qq_43682148/article/details/105320437
//贪心水题

signed main()
{
    IOS
    int n, k, c;
    string s;
    cin >> n >> k >> c;
    cin >> s;
    int cnt = 0;
    memset(l, -1, sizeof(l));
    memset(r, -1, sizeof(r));
    for (int i = 0; i < n && cnt < k ; ++i) {
        if (s[i] == 'x')continue;
        else {
            l[cnt++] = i;
            i += c;
        }
    }
    cnt = k - 1;
    for (int j = n - 1; j >= 0 && cnt >= 0 ; --j) {
        if (s[j] == 'x')continue;
        else {
            r[cnt--] = j;
            j -= c;
        }
    }
    for (int m = 0; m < k ; ++m) {
        if (l[m] == r[m] && l[m] != -1)cout << l[m] + 1 << endl;
    }
    return 0 ;
}