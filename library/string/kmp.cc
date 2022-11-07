// s[]是长文本，p[]是模式串，n是s的长度，m是p的长度
//求短模式串的Next数组：
for (int i = 2, j = 0; i <= m; i ++ ) {
    while (j && p[i] != p[j + 1]) j = ne[j];
    if (p[i] == p[j + 1]) j ++ ;
    ne[i] = j;
}
// 匹配
for (int i = 1, j = 0; i <= n; i ++ ) {
    while (j && s[i] != p[j + 1]) j = ne[j];
    if (s[i] == p[j + 1]) j ++ ;
    if (j == m)
    {
        j = ne[j];
        // 匹配成功后的逻辑
    }
}

/*
例题:给定一个模式串S，以及一个模板串P，所有字符串中只包含大小写英文字母以及阿拉伯数字。
模板串P在模式串S中多次作为子串出现。
求出模板串P在模式串S中所有出现的位置的起始下标。
第一行输入整数N，表示字符串P的长度。第二行输入字符串P。
第三行输入整数M，表示字符串S的长度。第四行输入字符串S。
输出:共一行，输出所有出现位置的起始下标（下标从0开始计数），整数之间用空格隔开。
1 <= N < 1e5  1 <= M < 1e6
*/
const int N = 100010, M = 1000010;
int n, m;
char p[N], s[M];
int ne[N];  // Next 数组是对短串而言的
int main() {
    cin >> n >> p + 1 >> m >> s + 1;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j++;
        ne[i] = j;
    }
    for (int i = 1, j = 0; i <= m; i++) {
        while (j && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j++;
        if (j == n) {
            cout << i - n << ' ';
            j = ne[j];
        }
    }
    return 0;
}