#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define mem(a,x) memset(a,x,sizeof(a))
#define pb push_back
#define pi pair<int, int>
#define mk make_pair
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
int a[200], len;

/*
优先队列放进1，2，3，4，5，6，7，8，9  每次取出一个，有三种变化形式可以放回去：

末尾连接上当前的个位数，个位数减一  个位数加1

https://blog.csdn.net/qq_41286356/article/details/105329129
*/
int main()
{
   int k;
   cin >> k;
   if (k <= 12) {
      cout << k;
      return 0;
   }
   priority_queue<ll, vector<ll>, greater<ll>> pq;
   for (int i = 1; i <= 9; i++)
      pq.push(i);

   int cnt = 0;
   ll ans;
   while (true) {
      ll num = pq.top();
      pq.pop();
      cnt++;

      if (cnt == k) {
         ans = num;
         break;
      }

      int ld = num % 10;
      ll num1 = num * 10 + ld;
      pq.push(num1);

      if (ld != 0) {
         num1 = num * 10 + ld - 1;
         pq.push(num1);
      }
      if (ld != 9) {
         num1 = num * 10 + ld + 1;
         pq.push(num1);
      }
   }
   cout << ans;
}