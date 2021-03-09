#include <bits/stdc++.h>
using namespace std;

//朴素BSGS 求a^x≡b(mod p)的最小x 前提是(a,p)=1 互质
//时间复杂度 O(sqrt(p)) p是模数

typedef long long ll;

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
    return -1;
}

int main() {
    int a, p, b;
    while (scanf("%d%d%d", &a, &p, &b), a || p || b) {
        int res = bsgs(a, b, p);
        if (res == -1) puts("No Solution");
        else printf("%d\n", res);
    }
    return 0;
}