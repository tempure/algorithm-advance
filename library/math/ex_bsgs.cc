//给定整数a,p,b求满足ax同余b(modp)的最小非负整数x
//每次用exgcd()求逆元递归，直到(a,p)互质，此时用朴素bsgs求出即可
//时间复杂度O(sqrt(p))
typedef long long ll;
const int INF = 1e9;
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
int bsgs(int a, int b, int p) {
    if (1 % p == b % p) return 0; //特判x = 0情况
    int k = sqrt(p) + 1; //分块长度
    unordered_map<int, int> hash;
    //a^t = a^(kx-y) ≡ b(mod p) 先枚举y
    for (int i = 0, j = b % p; i < k; i++) { //y：0~k-1
        hash[j] = i; //hash[j] 保存(b*a^y mod p, y) 只会保留后边较大的y
        j = (ll)j * a % p; //b*a^y mod p存入哈希表
    }
    int ak = 1; //a^k mod p
    for (int i = 0; i < k; i++) ak = (ll)ak * a % p;
    //枚举x
    for (int i = 1, j = ak;  i <= k; i++) {
        //找到答案直接返回 t = k*x-y
        if (hash.count(j)) return (ll)i * k - hash[j];
        j = (ll)j * ak % p;// a^(kx) mod p
    }
    return -INF;
}
int exbsgs(int a, int b, int p) {
    b = (b % p + p) % p;
    if (1 % p == b % p) return 0;
    int x, y;
    int d = exgcd(a, p, x, y); //求a,p的最大公约数
    if (d > 1) { //a,p还没互质就继续递归
        if (b % d) return -INF; //d不能乘除b 无解
        exgcd(a / d, p / d, x, y); //求a/d 模 p/d的逆元 x
        return exbsgs(a, (ll)b / d * x % (p / d), p / d) + 1; //求出的是t-1 要加上
    }
    //互质此时用朴素bsgs求出即可
    return bsgs(a, b, p);
}
int main() {
    int a, p, b;
    while (cin >> a >> p >> b, a || p || b) {
        int res = exbsgs(a, b, p);
        if (res <  0) puts("No Solution");
        else cout << res << endl;
    }
    return 0;
}