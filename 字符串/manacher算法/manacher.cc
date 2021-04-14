/*
O(n)求最长回文子串以及子串长度
mr为当前已经求出的回文串的最右边的边界
*/
const int N = 2e7 + 10; //插入#要开2倍+1
int n;
char a[N], b[N]; //原字符串和插之后的字符串
int p[N]; i为mid的最长回文半径p[i]
void init() {
    int k = 0;
    b[k++] = '$', b[k++] = '#';
    for (int i = 0; i < n; i++) b[k++] = a[i], b[k++] = '#';
    b[k++] = '^'; //结尾
    n = k;
}
void manacher() {
    int mr = 0, mid; //mr此时最右边界
    for (int i = 1; i < n; i++) {
        if (i < mr) p[i] = min(p[mid * 2 - i], mr - i); // i在此时大区间内
        else p[i] = 1;  //i在大区间外了 不能通过区间内对称点求出 重新算

        //求出i为mid的最长回文半径p[i]
        while (b[i - p[i]] == b[i + p[i]]) p[i]++;
        if (i + p[i] > mr) { //更新最右边界
            mr = i + p[i];
            mid = i;
        }
    }
}
int main() {
    scanf("%s", a);//待求的串
    n = strlen(a);
    init();
    manacher();
    int res = 0;
    for (int i = 0; i < n; i++) res = max(res, p[i]);
    printf("%d\n", res - 1);  //插入‘#’之后字符串的最长回文串半径长度减去1就是原串的最长回文子串长度
}