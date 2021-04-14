/*
核心思想：将字符串看成P进制数，P的经验值是131或13331，取这两个值的冲突概率低
技巧：取模的数用2^64，这样直接用unsigned long long存储，溢出的结果就是取模的结果
*/
typedef unsigned long long ULL;
ULL h[N], p[N]; // h[k]存储字符串前k个字母的哈希值, p[k]存储 P^k mod 2^64
// 初始化
p[0] = 1;
for (int i = 1; i <= n; i ++ ) {
    h[i] = h[i - 1] * P + str[i];
    p[i] = p[i - 1] * P;
}
// 计算子串 str[l ~ r] 的哈希值
ULL get(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}
/*
例题:给定一个长度为n的字符串，再给定m个询问，每个询问包含四个整数l1,r1,l2,r2，请你判断[l1,r1]和[l2,r2]这两个区间所包含的字符串子串是否完全相同。
串中只包含大小写英文字母和数字
第一行整数n和m，表示字符串长度和询问次数。
第二行一个长度为n的字符串，串中只包含大小写英文字母和数字
接下来m行，每行包含四个整数l1,r1,l2,r2，表示一次询问所涉及的两个区间。
注意，字符串的位置从1开始编号。 1 <= n,m <= 1e5
*/
typedef unsigned long long ull;
const int P = 131;
const int N = 100010;
ull p[N], h[N]; char s[N];
ull get(int l, int r) {
    return h[r] - h[l - 1] *  p[r - l + 1];
}
int main() {
    int n, m; p[0] = 1;
    cin >> n >> m >> s + 1;
    for (int i = 1; i <= n; i++) { //预处理o(N)
        h[i] = h[i - 1] * P + s[i] ; //char类型计算直接ascii码值
        p[i] = P * p[i - 1];
    }
    int l1, r1, l2, r2;
    while (m--) {
        cin >> l1 >> r1 >> l2 >> r2;
        if (get(l1, r1) == get(l2, r2))
            cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}