//https://oi-wiki.org/math/number-theory/du/#%E6%AC%A7%E6%8B%89%E5%87%BD%E6%95%B0%E5%89%8D%E7%BC%80%E5%92%8C
//模板题喵 直接粘贴板子喵
//ans = 303963552391
//解析见: https://pe.metaquant.org/pe072.html

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
const int maxn = 1e6 + 10;
long long T, n, pri[maxn], cur, mu[maxn], sum_mu[maxn];
bool vis[maxn];
map<long long, long long> mp_mu;

long long S_mu(long long x) {  // 求mu的前缀和
  if (x < maxn) return sum_mu[x];
  if (mp_mu[x]) return mp_mu[x];  // 如果map中已有该大小的mu值，则可直接返回
  long long ret = (long long)1;
  for (long long i = 2, j; i <= x; i = j + 1) {
    j = x / (x / i);
    ret -= S_mu(x / i) * (j - i + 1);
  }
  return mp_mu[x] = ret;  // 路径压缩，方便下次计算
}

long long S_phi(long long x) {  // 求phi的前缀和
  long long ret = (long long)0;
  long long j;
  for (long long i = 1; i <= x; i = j + 1) {
    j = x / (x / i);
    ret += (S_mu(j) - S_mu(i - 1)) * (x / i) * (x / i);
  }
  return (ret - 1) / 2 + 1;
}

int main() {
  // scanf("%lld", &T);
  T = 1;
  mu[1] = 1;
  for (int i = 2; i < maxn; i++) {  // 线性筛预处理mu数组
    if (!vis[i]) {
      pri[++cur] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cur && i * pri[j] < maxn; j++) {
      vis[i * pri[j]] = true;
      if (i % pri[j])
        mu[i * pri[j]] = -mu[i];
      else {
        mu[i * pri[j]] = 0;
        break;
      }
    }
  }
  for (int i = 1; i < maxn; i++)
    sum_mu[i] = sum_mu[i - 1] + mu[i];  // 求mu数组前缀和
  while (T--) {
    // scanf("%lld", &n);
    n = 1e6;
    printf("%lld %lld\n", S_phi(n), S_mu(n));
    printf("res = %lld\n", S_phi(n) - 1);
  }
  return 0;
}