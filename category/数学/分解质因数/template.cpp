#include <bits/stdc++.h>
using namespace std;

//分解质因数模板
//复杂度 O(sqrt(n))

const int N = 100010; // 数组开sqrt(N) 的数量级即可 看循环的次数
int p[N], c[N]; //p存储质因子 c存储幂次

int n, m;
void divide(int n) {
    m = 0;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            p[++m] = i; c[m] = 0; //一定要先存i 然后c[m]=0 顺序反会错
            while (n % i == 0) n /= i, c[m]++;
        }
    }

    //n为质数直接存 上边的for循环不会进入
    if (n > 1) p[++m] = n, c[m] = 1;

    //输出因子和对应次幂
    for (int i = 1; i <= m; i++)
        cout << p[i] << ' ' << c[i] << endl;
    cout << endl;
}

int main() {
    int x;
    cin >> n;
    while (n --) {
        cin >> x;
        divide(x);
    }
    return 0;
}