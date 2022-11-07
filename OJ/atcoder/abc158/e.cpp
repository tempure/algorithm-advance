#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
char s[N];
map<int, int> ma;

//倒着算是因为进制的高低位次幂
//https://www.cnblogs.com/zdragon1104/p/12441877.html
//https://blog.csdn.net/zhouzi2018/article/details/104729100

int main() {
    //freopen("in.txt","r",stdin);
    int n, p;
    scanf("%d%d%s", &n, &p, s + 1);
    ll ans = 0;
    if (10 % p == 0) {
        for (int i = 1; i <= n; i++) {
            if ((s[i] - '0') % p == 0) ans += i;
        }
    }
    else {
        int res = 0, t = 1;
        for (int i = n; i >= 1; i--) {
            ma[res]++;
            res = (res + (s[i] - '0') * t) % p;
            t = t * 10 % p;
            ans += ma[res];
        }
    }
    printf("%lld\n", ans);
    return 0;
}