#include <bits/stdc++.h>
using namespace std;

//FFT高精度乘法模板 O(N*logN)
//1e5 长度N大数

const int N = 300000; //A*B, A,B都是1e5位数，最高次幂2e5级别，2的整次幂最接近的为26w 开30w
const double PI = acos(-1);

struct Complex {
    double x, y;
    Complex operator+(const Complex &t) const {
        return {x + t.x, y + t.y};
    }
    Complex operator-(const Complex &t) const {
        return {x - t.x, y - t.y};
    }
    Complex operator*(const Complex &t) const {
        return {x*t.x - y * t.y, x * t.y + y * t.x};
    }
} a[N], b[N];//2个多项式的单位复根点表示/系数表示

char s1[N], s2[N]; //乘数
int res[N]; //反向存储最后的答案
int rev[N], bit, tot;

void fft(Complex a[], int inv) {
    for (int i = 0; i < tot; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < tot; mid *= 2) {
        auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)});
        for (int i = 0; i < tot; i += mid * 2) {
            auto wk = Complex({1, 0});
            for (int j = 0; j < mid; j++, wk = wk * w1) {
                auto x = a[i + j], y = wk * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y;
            }
        }
    }
}

int main() {
    scanf("%s%s", s1, s2);
    int n = strlen(s1) - 1, m = strlen(s2) - 1;
    for (int i = 0; i <= n; i++) a[i].x = s1[n - i] - '0'; //逆着存 fft需要次幂从低到高
    for (int i = 0; i <= m; i++) b[i].x = s2[m - i] - '0';
    while (1 << bit < n +  m + 1) bit ++;
    tot = 1 << bit;
    for (int i = 0; i < tot; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, 1), fft(b, 1); //DFT
    for (int i = 0; i < tot; i++) a[i] = a[i] * b[i];
    fft(a, -1); //IDFT

    //此时a[]存的是多项式从0次到高次的系数，系数可能会>10,而且会存在前导0
    //此时模拟一遍进位加法即可
    int k = 0;
    //t是进位 注意逆着存的进位关系 最后要去掉前导零
    for (int i = 0, t = 0; i < tot || t; i++) {
        t += a[i].x / tot + 0.5;
        res[k++] = t % 10;
        t /= 10;
    }
    while (k > 1 && !res[k - 1]) k--; //去掉后面补全二进制位的0
    for (int i = k - 1; i >= 0; i--) printf("%d", res[i]);

    return 0;
}