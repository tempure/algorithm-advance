#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1010;
int n, k, t = 1;
int a[N];
bool flag[N];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i ++ ) {
        scanf("%d", &a[i]);
        a[i] %= (n - i + 1);
        while (a[i]--) {
            if (t == n) t = 1;
            else t++;
            if (flag[t] == 1) a[i]++;
        }
        flag[t] = 1;
        cout << t << ' ';
        while (flag[t] == 1) t == n ? t = 1 : t++;
    }
}