/*给定一个 n 次多项式 F(x)=a0+a1x+a2x^2+...+anx^n
以及一个 m 次多项式 G(x)=b0+b1x+b2x^2+...+bmx^m
已知 H(x)=F(x)*G(x)=c0+c1x+c2x^2+...+c(n+m)x^(n+m)
计算并输出c0,c1,...,cn+m。1<=n,m<=1e5,0<=ai,bi<=9*/
const int N = 300010; //2^n,20w之后的是26w左右 直接开30w
const double PI = acos(-1);
int n, m;
struct Complex { //复数
    double x, y; //实部x 虚部 y
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
        if (i < rev[i]) swap(a[i], a[rev[i]]); //蝴蝶变换之后的下标
    for (int mid = 1; mid < tot; mid <<= 1) { //迭代求，从最小的段开始，每次向上归并
        auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)}); //w(n,1),n==2*mid
        for (int i = 0; i < tot; i += mid * 2) {
            auto wk = Complex({1, 0});
            for (int j = 0; j < mid; j++, wk = wk * w1) { //wk为w(n,k/2),也就是w(n,1)的k/2次方
                auto x = a[i + j], y = wk * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y; //左半边和右半边
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
        printf("%d ", (int)(a[i].x / tot + 0.5));//+0.5防止浮点误差系数保存在实部
    return 0;
}
//高精度乘高精度：1<=A与B的长度<=1e5
const int N = 300000; //1e5位数 乘2就是20w,二次幂最接近的为26w 开30w
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
} a[N], b[N];
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
    for (int i = 0; i <= n; i++) a[i].x = s1[n - i] - '0'; //逆着存
    for (int i = 0; i <= m; i++) b[i].x = s2[m - i] - '0';
    while (1 << bit < n +  m + 1) bit ++;
    tot = 1 << bit;
    for (int i = 0; i < tot; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, 1), fft(b, 1); //DFT
    for (int i = 0; i < tot; i++) a[i] = a[i] * b[i];
    fft(a, -1); //IDFT
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