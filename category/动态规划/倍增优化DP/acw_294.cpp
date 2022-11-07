#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
#include<string>
using namespace std;
string s1, s2;
int n1, n2;
long long f[105][32];

//https://www.acwing.com/video/1958/
//f[i][j]: 从 s1[i] 开始，需要多少个字符，才能生成 conn(s2, 2^j)
//f[i][0]: 从 s1[i] 开始，需要多少字符才能生成一个 s2 (暴力预处理)


void solve() {
    memset(f, 0, sizeof(f));
    for (int i = 0; i < s1.size(); i++) {
        int pos = i;
        f[i][0] = 0;
        for (int j = 0; j < s2.size(); j++) {
            int cnt = 0;
            while (s1[pos] != s2[j]) {
                pos = (pos + 1) % s1.size();
                if (++cnt >= s1.size()) {
                    cout << 0 << endl;
                    return;
                }
            }
            pos = (pos + 1) % s1.size();
            f[i][0] += cnt + 1;  // why cnt + 1 ??
        }
    }
    for (int j = 1; j <= 30; j++)
        for (int i = 0; i < s1.size(); i++)
            f[i][j] = f[i][j - 1] + f[(i + f[i][j - 1]) % s1.size()][j - 1];
    long long m = 0;
    int st = 0;
    // for (int st = 0; st < s1.size(); st++) {
    long long x = st, ans = 0;
    for (int k = 30; k >= 0; k--) {
        if (x + f[x % s1.size()][k] <= s1.size()*n1) {
            x += f[x % s1.size()][k];
            ans += 1 << k;
        }
    }
    m = max(m, ans);
    // }
    cout << m / n2 << endl;
}

int main()  {
    while (cin >> s2 >> n2 >> s1 >> n1) solve();
}

// 作者：lydrainbowcat
// 链接：https://www.acwing.com/activity/content/code/content/592426/
// 来源：AcWing
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。