#include <iostream>
using namespace std;

//分解质因数求单个数的欧拉函数 O(sqrt(N))
//重要的性质：一个数 X 最多只有一个大于等于 sqrt(X) 的质因子，注意不是因子是质因子
//因子不一定，比如 36 就有12， 18 两个大于6的因子

int n;

int phi(int n) {
    int ans = n;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    //最后如果n还是>1，说明这就是大于sqrt(n)的唯一质因子 计算即可
    //因为 for 循环只枚举了 小于等于 sqrt(n) 的质因子
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

int main() {
    cin >> n;
    while (n --) {
        int x; cin >> x;
        cout << phi(x) << endl;
    }

    return 0;
}