//分解质因子求某个数欧拉函数 复杂度sqrt(n)
ll get_euler(ll c) {
    ll res = c;
    for (int i = 2; i <= c / i; i++)
        if (c % i == 0) {
            while (c % i == 0) c /= i;
            res = res / i  * (i - 1);
        }
    if (c > 1) res = res / c * (c - 1);
    return res;
}
//线性筛 求1 ~ N中所有数欧拉函数模板
const int N = 1010;
int n;
int primes[N], cnt;
int phi[N]; //欧拉函数
bool v[N];
void get_euler(int n) { //线性筛求欧拉函数
    memset(v, 0, sizeof v);
    cnt = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!v[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            int t = primes[j] * i;
            v[t] = 1;
            if (i % primes[j] == 0) {
                phi[t] = phi[i] * primes[j];
                break;
            }
            phi[t] = phi[i] * (primes[j] - 1);
        }
    }
}
/*
例题:给定整数N，求1<=x,y<=N且GCD(x,y)为素数的数对(x,y)有多少对。
*/
//gcd(a,b) == p, 那么gcd(a/p, b/p) == 1，枚举n内所有素数
//而求1~n中有序互质对x，y的个数，可以令y >= x, 当y = x时，有且只有y = x = 1互质，
//当y > x时，确定y以后符合条件的个数x就是phiy
// 所以有序互质对的个数为（1 ~ n/p）的欧拉函数之和乘2减1（要求的是有序互质对，乘2以后减去（1， 1）多算的一次）
// 那么就只需要先筛出欧拉函数再求个前缀和就可以了
const int N = 1e7 + 10;
int n;
int primes[N], cnt;
int phi[N]; //欧拉函数
bool v[N];
ll s[N];  //欧拉函数值的前缀和
void get_euler(int n) { //线性筛求欧拉函数
    memset(v, 0, sizeof v);
    cnt = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!v[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            int t = primes[j] * i;
            v[t] = 1;
            if (i % primes[j] == 0) {
                phi[t] = phi[i] * primes[j];
                break;
            }
            phi[t] = phi[i] * (primes[j] - 1);
        }
    }
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + phi[i];
}
int main() {
    cin >> n;
    get_euler(n);
    ll res = 0;
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        res += s[n / p] * 2 - 1;
    }
    cout << res << endl;
    return 0;
}