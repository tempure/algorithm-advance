/*给定一个长度为 N 的数列 A，以及 M 条指令
C l r d，表示把 A[l],A[l+1],…,A[r] 都加上 d
Q l r，表示询问数列中第 l~r 个数的和。
对于每个询问，输出一个整数表示答案。
1<=N,M<=1e5,|d|<=10000,|A[i]|<=1e9
段内暴力求和/修改，完整段直接整段标记修改,复杂度O(M*sqrt(N))*/
typedef long long ll;
const int N = 100010, M = 350;//M是块数量
int n, m, len; //len是每个块的长度
ll add[M], sum[M]; //add[]是懒标记 sum[]是块元素的sum
int w[N];
int get(int i) {
    return i / len; //返回每个位置的点所在的块
}
void change(int l, int r, int d) {
    if (get(l) == get(r)) { //特判在同一个块中的情况 直接暴力
        for (int i = l; i <= r; i++) {
            w[i] += d;
            sum[get(i)] += d;
        }
    }
    else {
        int i = l, j = r; //先计算左右2段不完整的块 然后计算完整的块
        while (get(i) == get(l)) w[i] += d, sum[get(i)] += d, i++;
        while (get(j) == get(r)) w[j] += d, sum[get(j)] += d, j--;
        for (int k = get(i); k <= get(j); k++) sum[k] += len * d, add[k] += d;
    }
}
ll query(int l, int r) {
    ll res = 0;
    if (get(l) == get(r)) {
        //add就是为了计算不完整的块 完整的块只需要用到sum
        for (int i = l; i <= r; i++) res += w[i] + add[get(i)];
    }
    else {
        int i = l, j = r;
        while (get(i) == get(l)) res += w[i] + add[get(i)], i++;
        while (get(j) == get(r)) res += w[j] + add[get(j)], j--;
        for (int k = get(i); k <= get(j); k++) res += sum[k];
    }
    return res;
}
int main() {
    scanf("%d%d", &n, &m);
    len = sqrt(n);//一般块长是根号N
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        sum[get(i)] += w[i];
    }
    char op[2];
    int l, r, d;
    while (m --) {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C') {
            scanf("%d", &d);
            change(l, r, d);
        }
        else printf("%lld\n", query(l, r));
    }
    return 0;
}