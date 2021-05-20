/*
详细题解：https://www.acwing.com/solution/content/23435/

集合博弈:sg函数的参数，就是该集合的大小，对于一个集合大小x，那么sg(x)就是确定的，也就是递归该点的递归树是确定的,记录下sg(x)可以减少递归次数
对于每个集合都求出sg(x)后，将当前的状态当作NIM博弈。
每个集合最终都会走到sg(x) == 0 的必败状态，所以某点sg(x)如果不为0，那么其出边节点必然有0，可以走到必败状态
递归细节：如果当前节点的数量已经不能再拿了，也就是小于所有集合元素，那么就是必败状态，这在sg()函数的第二个for循环里面会将其f[x]=0

最终sg图上的节点编号是当前集合大小x，节点权值为sg函数值f[x]
*/
#include <bits/stdc++.h>
using namespace std;

const int M = 10010;
const int N = 110;
int f[M], s[N];
int n, m;

int sg(int x) {
    if (f[x] != -1) return f[x];
    unordered_set<int> S;

    for (int i = 0; i < m; i++) {
        int sum = s[i];
        if (x >= sum) S.insert(sg(x - sum));
    }

    for (int i = 0; ; i ++) { //对于一个必败状态，也就是小于集合中所有元素，其f[x] = 0;
        if (!S.count(i))
            return f[x] = i;
    }
}

int main() {
    cin >> m;
    for (int i = 0; i < m; i++) cin >> s[i];
    memset(f, - 1, sizeof f);
    int res = 0;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        res ^= sg(x);
    }

    if (res == 0) cout << "No" << endl;
    else cout << "Yes" << endl;

    return 0;
}