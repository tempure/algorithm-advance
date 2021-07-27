#include <iostream>
using namespace std;

/*
注意最小正整数解
通解x = x0 + k * b, 那么求最小正整数解就是((x0 % b) + b) % b
可以理解为：x0 为正的时候，直接mod b即可
当x0为负的时候，先加上很多个b让其为正，然后再mod，就等价上述x0为正的理解一样
*/

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

void solve() {
    int a, b;
    cin >> a >> b;
    int x, y;
    exgcd(a, b, x, y);
    cout << ((x % b) + b) % b << endl;
}

int main() {
    solve();
    return 0;
}