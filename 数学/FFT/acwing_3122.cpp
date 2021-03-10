#include <bits/stdc++.h>
using namespace std;

const int N = 300010; //2^n  20w之后的是26w左右 直接开30w
const double PI = acos(-1);

int n, m;
struct Complex { //复数
    double x, y;
    Complex operator+(const Complex &t) const {
        return {x + t.x, y + t.y};
    }
    Complex operator- (const Complex &t) const {
        return {x - t.x, y - t.y};
    }
    Complex operator* (const Complex& t) const {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
} a[N], b[N];

int rev[N], bit, tot; //bit是二进制总位数 tot是序列补全之后的长度

void fft(Complex a[], int inv) {
    for (int i = 0; i < tot; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < tot; mid <<= 1) {
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
    scanf("%d%d", &n, &m);
    //2个多项式系数
    for (int i = 0; i <= n; i++) scanf("%lf", &a[i].x);
    for (int i = 0; i <= m; i++) scanf("%lf", &b[i].x);
    while ((1 << bit) < n + m + 1) bit ++;
    tot = 1 << bit; //计算补全为2的整次幂的序列长度
    for (int i = 0; i < tot; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, 1), fft(b, 1); //DFT;
    for (int i = 0; i < tot; i++) a[i] = a[i] * b[i];
    fft(a, -1);  //IDFT;

    for (int i = 0; i <= n + m; i++)
        printf("%d ", (int)(a[i].x / tot + 0.5)); //+0.5是防止浮点数误差

    return 0;
}