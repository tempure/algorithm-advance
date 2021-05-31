#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;

const int mod = 9901;
int A, B;

unordered_map<int, int> primes; //离散化质因子

void divide(int n) {
    for (int i = 2; i <= n / i; i++)
        if (n % i == 0)
            while (n % i == 0) {
                primes[i]++;
                n /= i;
            }
    if (n > 1) primes[n] ++; //大于sqrt(N)的质因子
}

ll qmi(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

//递归分治求 p^0+p^1+....+p^(k-1)
ll sum(int p, int k) {
    if (k == 1) return 1;
    if (k % 2 == 0) return (qmi(p, k / 2) + 1) * sum(p, k / 2) % mod;
    else return (qmi(p, k - 1) + sum(p, k - 1)) % mod;
}

ll calc(int A, int B) {
    divide(A);
    ll res = 1;
    for (auto it : primes) {
        int p = it.first, k = it.second * B;
        res = res * sum(p, k + 1) % mod;
    }
    return res;
}

int main() {
    cin >> A >> B;
    if (!A) {
        cout << 0 << endl;
        return 0;
    }
    cout << calc(A, B) << endl;

    return 0;
}