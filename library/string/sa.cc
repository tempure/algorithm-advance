/*给定一个长度为 n 的字符串，只包含大小写英文字母和数字。
将字符串中的 n 个字符的位置编号按顺序设为1~n。
并将该字符串的 n 个非空后缀用其起始字符在字符串中的位置编号表示。
对这 n 个非空后缀字典序排序，给定两个数组SA和Height。
SA[i]记录排名为i非空后缀的编号,Height[i]记录排名为i非空后缀与排名i−1非空后缀的最长公共前缀的长度（1<=i<=n）。规定 Height[1]=0。输出这两个数组。*/
//倍增实现SA 复杂度O(N*logN)
const int N = 1000010;
int n, m; char s[N];
//rk[i]是第i个后缀的排名
int sa[N], x[N], y[N], c[N], rk[N], height[N];
void get_sa() {
    for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
    //统计小于每个关键字的元素有多少个
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    //从后往前依次确定每个元素的排名 统计一个减一个
    for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;
    //log(N)轮基数排序
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        //将所有后缀按照第二关键字排序
        //最后k个字符，没有第二关键字，最小所以先存下来
        for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k;
        //再按照第一关键字排序
        for (int i = 1; i <= m; i ++ ) c[i] = 0;
        for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
        //将当前所有后缀的前2k个字符离散化
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
/*SDOI2016《生成魔咒》：初始串S为空，操作n次，每次往最后加一个字符x，求每次加后生成子串的数量1<=n<=1e5,1<=x<=1e9*/
/*所有的子串就是“所有后缀的所有前缀”
对于一个静态的查询，SA排序之后考虑sa[i]和sa[i-1]的后缀，sa[i]中新的前缀的个数就是后缀i的长度减去height[i]
所以累加所有的len[i] - height[i]即可,但有修改操作的问题需要维护height[]和sa[]。逆序存储字符串，然后每次在开头插入，这样删除开头的一个字符，不会影响后边的后缀
所以直接将所有插入的字符一次性全部插入，然后离线删除每一个字符，同时维护sa[],height[],对于sa[]使用双链表维护顺序，删除O(1)，每个链表元素代表一个sa[]后缀开头
删除后缀sa[i],sa[i+1]会被影响, 因为height[i]是和前一个后缀的lcp,所以删去sa[i]后缀后，更新为和sa[i-1]的lcp。此题的x最大1e9需要离散化*/
typedef long long ll;
const int N = 100010; //离散化之后的个数
int n, m;
int s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];
int u[N], d[N];
ll ans[N];
int get(int x) { //离散化
    static unordered_map<int, int> hash;
    if (hash.count(x) == 0) hash[x] = ++m;
    return hash[x];
}
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
    scanf("%d", &n);
    //逆序读入 然后离散化
    for (int i = n; i; i--)
        scanf("%d", &s[i]), s[i] = get(s[i]);
    get_sa();
    get_height();
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        //n - sa[i] + 1就是排名i的后缀的长度
        res += n - sa[i] + 1 - height[i]; //先加上所有操作之后的结果，然后再逐个减去
        u[i] = i - 1, d[i] = i + 1; //双链表 维护排序之后的后缀
    }
    d[0] = 1, u[n + 1] = n;
    for (int i = 1; i <= n; i++) {
        ans[i] = res; //答案逆序存储
        //k是准备删去的后缀i, j是i排名后一位的后缀
        int k = rk[i], j = d[k];
        //删掉i会影响排名i和i+1的lcp
        //此时排名i+1的后缀应该更新为和i-1的lcp
        //后缀的长度减去height就是新的前缀的数量
        res -= n - sa[k] + 1 - height[k];
        //减去i和j之后，重新计算之后再加上
        res -= n - sa[j] + 1 - height[j];
        height[j] = min(height[j], height[k]); //更新lcp
        res += n - sa[j] + 1 - height[j];
        d[u[k]] = d[k], u[d[k]] = u[k]; //链表删除
    }
    for (int i = n; i; i--)
        printf("%lld\n", ans[i]); //逆序输出答案
    return 0;
}