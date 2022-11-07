//Tire模板
int son[N][26], cnt[N], idx;
// 0号点既是根节点，又是空节点
// son[][]存储树中每个节点的子节点
// cnt[]存储以每个节点结尾的单词数量

// 插入一个字符串
void insert(char *str) {
    int p = 0;
    for (int i = 0; str[i]; i ++ ) {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];
    }
    cnt[p] ++ ;
}

// 查询字符串出现的次数
int query(char *str) {
    int p = 0;
    for (int i = 0; str[i]; i ++ ) {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

/*
例题:最大异或对
在给定的N个整数A1，A2……AN中选出两个进行xor（异或）运算，得到的结果最大是多少？
第一行输入一个整数N,第二行输入N个整数A1～AN。
1 <= N <= 1e5, 0 <= Ai < 2^31
*/
const int N = 100010, M  = 3000010;
int n;
//每个数最多二进制表示31位长 N个数
int son[M][2], idx; //注意对于特殊son数组 第一维要开总共的节点个数
int a[N];
//此题略有贪心思路： 从最高位开始异或 原因是低位对于数大小的贡献
//远小于高位 数大小由高位决定 复杂度n*log(n)
void insert(int x) {
    int p = 0;
    for (int i = 30; ~i ; i --) { //从高位到低位存 所以逆着来
        int &s = son[p][x >> i & 1];  // >> i 是第 i + 1 位  所以循环最大30
        if (!s) s = ++idx;
        p = s;
    }
}
int query(int x) {
    int res = 0, p = 0;
    for (int i = 30; ~i; i--) {
        int s = x >> i & 1;
        if (son[p][!s]) {
            res += 1 << i;  //该位对于答案的贡献
            p = son[p][!s];
        } else p = son[p][s]; //不存在不同的值 就只能选择相同的二进制位
    }
    return res;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        insert(a[i]);
    }
    int res = 0;
    for (int i = 0; i < n ; i++) res = max(res, query(a[i]));
    cout << res << endl;
    return 0;
}