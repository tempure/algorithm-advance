//分类讨论题。。。
//https://www.10qianwan.com/articledetail/612986.html
//https://blog.csdn.net/qq_40655981/article/details/107156038

/*
1.先看<0,>0的数够不够k个，不够答案显然为0
2.看答案是否>0
----2.1如果答案>0，那么显然是选偶数个<0的，剩下全是>0的，如果k是奇数的话先拿一个>0最大的，然后贪心每次从>0,<0里面 拿两个乘积最大的。
3.答案<0的时候：那么显然贪心拿绝对值最小的。。。特判一下=0的情况
*/

#include<bits/stdc++.h>
#define ll long long
#define maxn 1005
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

inline ll read()
{
    ll x = 0, w = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') w = -1; c = getchar();}
    while (c <= '9' && c >= '0') {x = (x << 1) + (x << 3) + c - '0'; c = getchar();}
    return w == 1 ? x : -x;
}
const ll mod = 1e9 + 7;
const int N = 2e5 + 10;
ll a[N], n, k;
vector<ll>G1, G2;
bool cmp2(ll x, ll y)
{
    return abs(x) < abs(y);
}
bool cmp1(ll x, ll y)
{
    return x > y;
}
bool cmp3(ll x, ll y)
{
    return x < y;
}
void run1()
{
    //puts("***");
    sort(G1.begin(), G1.end(), cmp1);
    sort(G2.begin(), G2.end(), cmp3);
//    for(ll v:G1) printf("%lld ",v);puts("");
//    for(ll v:G2) printf("%lld ",v);puts("");

    int id1 = 0, id2 = 0;
    ll ans = 1;
    if (k % 2) {
        ans = G1[id1++];
    }
    while (id1 + 1 < G1.size() && id2 + 1 < G2.size() && id1 + id2 + 2 <= k) {
        //printf("id1:%d id2:%d\n",id1,id2);

        if (G1[id1]*G1[id1 + 1] > G2[id2]*G2[id2 + 1]) {
            ans = ans * G1[id1] % mod * G1[id1 + 1] % mod;
            id1 += 2;
        }
        else {
            ans = ans * G2[id2] % mod * G2[id2 + 1] % mod;
            id2 += 2;
        }
    }
    //printf("id1:%d id2:%d sz:%d\n",id1,id2,G1.size());

    while (id2 + 1 < G2.size() && id1 + id2 + 2 <= k) {
        ans = ans * G2[id2] % mod * G2[id2 + 1] % mod;
        id2 += 2;
    }
    while (id1 + 1 < G1.size() && id1 + id2 + 2 <= k) {
        ans = ans * G1[id1] % mod * G1[id1 + 1] % mod;
        id1 += 2;
    }
    //if(id1+id2<k) ans=ans*G1[id1++]%mod;
    printf("%lld\n", (ans + mod) % mod);

}
int main()
{
    n = read(), k = read();
    int zero = 0;
    rep(i, 1, n)
    {
        a[i] = read();
        if (a[i] > 0) G1.emplace_back(a[i]);
        else if (a[i] < 0) G2.emplace_back(a[i]);
        else zero++;
    }
    if (G2.size() - (G2.size() & 1) + G1.size() >= k && (k & 1) <= G1.size()) {
        run1();
    }
    else if (zero) {
        puts("0");
    }
    else {
        sort(a + 1, a + 1 + n, cmp2);
        ll ans = 1;
        rep(i, 1, k) ans = ans * a[i] % mod;
        printf("%lld\n", (ans + mod) % mod);
    }

}