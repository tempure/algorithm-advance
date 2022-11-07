//高精度加法
// C = A + B, A >= 0, B >= 0
vector<int> add(vector<int> &A, vector<int> &B)
//例题：给定两个正整数，计算它们的和。
//1 <= 整数长度 <= 100000
const int N = 1e6 + 10;
vector<int> add(vector<int> &a, vector<int> &b) {
    int t = 0; vector<int> c;
    for (int i = 0; i < a.size() || i < b.size(); i++) {
        if (i < a.size()) t += a[i];
        if (i < b.size()) t += b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    if (t) c.push_back(1);
    return c;
}
int main() {
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    //初始逆序存储 返回的结果也是逆序存储的vector
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--)
        B.push_back(b[i] - '0');
    auto c = add(A, B);
    for (int i = c.size() - 1; i >= 0; i--) printf("%d", c[i]);
}
//数组实现解法:
const int N = 1e6 + 10;
int a[N], b[N], sum[N];
void add(int c[], int a[], int b[]) {
    for (int i = 0, t  = 0 ; i < N; i++) {
        t += a[i] + b[i];
        c[i] = t % 10;
        t /= 10;
    }
}
int main() {
    string sa, sb;
    cin >> sa >> sb;
    //逆序存储
    for (int i = sa.size() - 1, j = 0; i >= 0; i--)
        a[j++] = sa[i] - '0';
    for (int i = sb.size() - 1, j = 0; i >= 0; i--)
        b[j++] = sb[i] - '0';
    add(sum, a, b);
    int i = N - 1;
    while (!sum[i]) i --;//去除前导零
    while (i >= 0) printf("%d", sum[i--]);
    return 0;
}
//高精度减法
// C = A - B, 满足A >= B, A >= 0, B >= 0
vector<int> sub(vector<int> &A, vector<int> &B)
//例题：给定两个正整数，计算它们的差，计算结果可能为负数。
//1 <= 整数长度 <= 1e5
typedef vector<int> VI;
bool cmp(VI &a, VI &b) { //减法需要大数减去小数 分类讨论
    if (a.size() != b.size()) return a.size() > b.size();
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] > b[i];
    }
    return true;
}
VI sub(VI &a, VI &b) {
    int t = 0;  VI c;
    for (int i = 0; i < a.size(); i++) {
        t = a[i] - t;
        if (i < b.size()) t -= b[i];
        c.push_back((t + 10) % 10);
        if (t < 0) t = 1; else t = 0;
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}
int main() {
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    //逆序读入
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--)
        B.push_back(b[i] - '0');
    if (cmp(A, B)) {
        auto c = sub(A, B);
        for (int i = c.size() - 1; i >= 0; i--)
            printf("%d" , c[i]);
    }
    else {
        auto c = sub(B, A);
        printf("-");  //结果是负数  先输出负号 逆序输出
        for (int i = c.size() - 1; i >= 0; i--)
            printf("%d" , c[i]);
    }
    return 0;
}
//高精度乘低精度
// C = A * b, A >= 0, b > 0
vector<int> mul(vector<int> &A, int b)
//例题：给定两个正整数A和B，请你计算A * B的值。
//1<= A的长度 <= 100000, 0<= B <=10000
typedef vector<int> VI;
VI mul(VI &a, int b) {
    int t = 0;
    VI c;  //答案
    for (int i = 0; i < a.size() || t; i++) {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}
int main() {
    string a; int b; VI A;
    cin >> a >> b;
    if (b == 0 || a[0] == 0) { //特判0的情况
        cout << 0 << endl;
        return 0;
    }
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    auto c = mul(A, b);
    for (int i = c.size() - 1; i >= 0; i--)
        printf("%d", c[i]);
    return 0;
}
//高精度除以低精度
// A / b = C ... r, A >= 0, b > 0
vector<int> div(vector<int> &A, int b, int &r)
//例题:给定两个非负整数A，B，请你计算 A / B的商和余数。
//1 <= A的长度 <= 100000 ,1 <= B <= 10000, B 一定不为0
typedef vector<int> VI;
VI div(VI &a, int b, int &r) { //r是余数
    r = 0;
    VI c;  //答案
    for (int i = a.size() - 1; i >= 0; i--) {
        r = r * 10 + a[i];
        c.push_back(r / b);
        r %= b;
    }
    reverse(c.begin(), c.end());
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}
int main() {
    string a; int b;
    cin >> a >> b;
    int r = 0; VI A;
    //逆序读入
    for (int i  = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    auto c = div(A, b, r);
    for (int i = c.size() - 1; i >= 0; i--)
        printf("%d", c[i]);
    printf("\n");
    printf("%d\n", r); //余数
}