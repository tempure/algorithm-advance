#include <iostream>
using namespace std;

//分组背包 没有优化 直接转移

const int N = 110;
int v[N][N], w[N][N], s[N];
int f[N];
int n, m;

//二维写法
int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        for (int j = 0; j < s[i]; j++)
            cin >> v[i][j] >> w[i][j];
    }

    for (int i = 1; i <= n; i++) //第i组，每一组只能选一种，所以要逆序j
        for (int j = m; j >= 0; j--)
            for (int k = 0; k < s[i]; k++) //选第i组物品的某种物品k
                if (v[i][k] <= j) f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
    cout << f[m] << endl;

    return 0;
}

//一维写法
#include <iostream>
using namespace std;

const int N = 110;

int n, m;
int f[N], v[N], w[N];

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) { //边读边算
        int s; cin >> s;
        for (int j = 0; j < s; j++) cin >> v[j] >> w[j];
        for (int j = m; j >= 0; j--)
            for (int k = 0; k < s; k++)
                if (v[k] <= j) f[j] = max(f[j], f[j - v[k]] + w[k]);
    }
    cout << f[m] << endl;

    return 0;
}