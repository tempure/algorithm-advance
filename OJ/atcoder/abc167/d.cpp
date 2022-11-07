#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
using LL = long long;

//这个循环节 是从半路开始的 不一定是一个排列，，，
//https://blog.csdn.net/weixin_44851176/article/details/106043255

int a[N];
int dis[N * 2], cnt;
bool st[N];
int main()
{
    LL n, k;
    cin >> n >> k;
    int tt;
    for (int i = 1; i <= n; i++) cin >> tt, a[i] = tt;
    int x = 1, t = 0, next;
    while (!st[x] && t < k) {
        st[x] = 1;
        dis[++cnt] = x;
        x = a[x];
        t++;
    }
//  for(int i=1;i<=cnt;i++) cout<<dis[i]<<" ";
//  cout<<endl;
    if (t == k) cout << x << endl;
    else {
        int pos = 1;
        for (int i = 1; i <= cnt; i++) {
            if (dis[i] == x) pos = i;
        }
        //cout<<pos<<endl;
        int xun = cnt - pos + 1;
        k = k - pos + 1;
        k %= xun;
        cout << dis[pos + k] << endl;
    }
    return 0;
}