#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MD = 998244353;
const int N = 2e5 + 5;
pair<int, int> p[N];
stack<pair<int, int> > st;
int f[N];

//https://www.cnblogs.com/zdragon1104/p/12441877.html
/*
首先先将N个机器人按Xi升序排好序，令f[x]代表x~n的集合数，当第x个机器人不激活时，那么就是f[x+1]；
当第x个机器人被激活时，那么就是f[y]，y代表离x最近的不被x影响（包括间接）的机器人。
*/
//集合这个概念用DP算有点费解 ....
//以及状态定义是怎么来的....

int main() {
    //freopen("in.txt","r",stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].first, &p[i].second);
    }
    sort(p + 1, p + n + 1);
    f[n + 1] = 1;
    for (int i = n; i >= 1; i--) {
        int t = p[i].first + p[i].second, nex = i + 1;
        while (!st.empty() && t > p[st.top().first].first) {
            nex = st.top().second;
            st.pop();
        }
        st.push({i, nex});
        f[i] = (f[i + 1] + f[nex]) % MD;
    }
    printf("%d\n", f[1]);
    return 0;
}