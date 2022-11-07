/*
字符串最小表示法 双指针O(n)
模板题：给出2个字符串，问环形拓扑序列是否相同，即最小表示。
若相同输出Yes以及最小表示，否则输出No
输入样例：
2234342423
2423223434
输出样例：
Yes
2234342423
*/
const int N = 2000010;//拆环为链，复制一遍 开2倍
int n;//
char a[N], b[N];
int get_min(char s[]) {
    int i = 0, j = 1;
    while (i < n && j < n) {
        int k = 0;
        while (k < n && s[i + k] == s[j + k]) k++;
        if (k == n) break; //该串有循环节直接break得到答案
        if (s[k + i] > s[j + k]) i += k + 1;
        else  j += k + 1;
        if (i == j) j ++;
    }
    int k = min(i, j); //无论何种情况，两个指针中较小的那个就是最小表示法的开头
    s[k + n] = 0; //截断便于输出
    return k;
}
int main() {
    scanf("%s%s", a, b);
    n = strlen(a);
    memcpy(a + n, a, n);
    memcpy(b + n, b, n);
    int x = get_min(a), y = get_min(b);
    if (strcmp(a + x, b + y)) puts("No");
    else {
        puts("Yes");
        puts(a + x);
    }
    return 0;
}