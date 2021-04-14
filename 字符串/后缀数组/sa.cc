/*给定一个长度为 n 的字符串，只包含大小写英文字母和数字。
将字符串中的 n 个字符的位置编号按顺序设为1~n。
并将该字符串的 n 个非空后缀用其起始字符在字符串中的位置编号表示。
对这 n 个非空后缀字典序排序，给定两个数组SA和Height。
SA[i]记录排名为i非空后缀的编号,Height[i]记录排名为i非空后缀与排名i−1非空后缀的最长公共前缀的长度（1<=i<=n）。规定 Height[1]=0。输出这两个数组。*/
//倍增实现SA 复杂度O(N*logN)
const int N = 1000010;
int n, m; char s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];
void get_sa() {
    for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k;
        for (int i = 1; i <= m; i ++ ) c[i] = 0;
        for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i ++ )
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
        if (num == n) break;
        m = num;
    }
}
void get_height() {
    for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i ++ ) {
        if (rk[i] == 1) continue;
        if (k) k -- ;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
        height[rk[i]] = k;
    }
}
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1), m = 122;
    get_sa();
    get_height();
    for (int i = 1; i <= n; i ++ ) printf("%d ", sa[i]);
    puts("");
    for (int i = 1; i <= n; i ++ ) printf("%d ", height[i]);
    puts("");
    return 0;
}