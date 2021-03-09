#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int qmi(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = (ll)res * a % p;
        a = (ll) a * a % p;
        b >>= 1;
    }
    return res;
}

int inv(int a, int p) { //求逆元 p为质数
    return qmi(a, p - 2, p);
}

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int bsgs(int a, int b, int p) { //a^x≡b(mod p)
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
    return -2;
}

int main() {
    int T;
    cin >> T;
    while (T --) {
        int p, a, b, x1, t;
        cin >> p >> a >> b >> x1 >> t;
        if (a == 0) {
            if (x1 == t) puts("1");
            else if (b == t) puts("2");
            else puts("-1");
        }
        else if (a == 1) {
            if (b == 0) puts(t == x1 ? "1" : "-1");
            else {
                int x, y;
                exgcd(b, p, x, y);
                x = ((ll)x * (t - x1) % p + p) % p;
                cout << x + 1 << endl;
            }
        }
        else {
            int C = (ll)b * inv(a - 1, p) % p;
            int A = (x1 + C) % p;
            if (A == 0) {
                int u = (-C + p) % p;
                puts(u == t ? "1" : "-1");
            }
            else {
                int B = (t + C) % p;
                cout << bsgs(a, (ll)B * inv(A, p) % p, p) + 1 << endl;
            }
        }
    }
    return 0;
}