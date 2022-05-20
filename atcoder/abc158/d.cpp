#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define rush() int T;scanf("%d",&T);while(T--)
#define mm(a,b) memset(a,b,sizeof(a))
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define sc(a) scanf("%d",&a)
#define sc2(a,b) scanf("%d%d",&a,&b)
#define pf(a) printf("%d\n",a)
#define pf2(a,b) printf("%d %d\n",a,b)
#define p_f(a) printf("%d ",a)
#define fi first
#define se second
#define db double
#define ll long long
using namespace std;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const db eps = 1e-9;
deque<char>q;
string s;
int qq, com, f;
char c;
int main()
{
    cin >> s >> qq;
    rep(i, 0, s.size() - 1)q.push_back(s[i]);
    bool flag = true;
    rep(i, 1, qq) {
        cin >> com;
        if (com == 1)flag = !flag;
        else {
            cin >> f >> c;
            if (flag) {
                if (f == 1)q.push_front(c);
                else q.push_back(c);
            } else {
                if (f == 2)q.push_front(c);
                else q.push_back(c);
            }
        }
    }
    if (flag) {
        while (!q.empty()) {
            cout << q.front();
            q.pop_front();
        }
    } else {
        while (!q.empty()) {
            cout << q.back();
            q.pop_back();
        }
    }
    return 0;
}
//https://blog.csdn.net/zhouzi2018/article/details/104729100