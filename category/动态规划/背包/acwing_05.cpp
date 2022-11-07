/*
二进制拆分优化多重背包 O(N*V*logS)
将每种物品的数量s[i]用二进制拆分，用二进制倍增的思维来凑一个数，这样枚举s[i]就变为log(S[i])复杂度
凑的过程有个细节：如果s[i]不是2的次幂，那么需要补上一个数让其拆分之后的和等于s[i],因为枚举下一个二次幂肯定会超过s[i]
凑的话找的是一个最大的不会超过s[i]的2的次幂
其实拆分就相当于把物品打包，打包之后看作一个大的物品，减少物品数量
拆分之后，将所有打包之后的状态当作 01背包 处理即可,因为打包之后就没有“种”的概念了，相当于一个全新的问题
全新的问题每个物品都是新的体积/价值，而且只能选一次,那么就是01背包了
*/

#include <iostream>
using namespace std;

const int N = 25000; //1000 * log(2000) N*log(S)

int n, m;
int v[N], w[N];
int f[N];

int main() {
	cin >> n >> m; //物品种类 背包总体积
	int cnt = 0; //打包之后物品的数量

	for (int i = 1; i <= n; i++) {
		int a, b, s; //a -> v[i]  b->w[i]
		cin >> a >> b >> s; //开始拆分s 重新打包

		int k = 1;
		while (k <= s) {
			cnt++; //一个包
			v[cnt] = a * k;
			w[cnt] = b * k;
			s -= k;
			k *= 2;
		}

		if (s > 0) { //s[i]不是二的次幂，最后补上缺的
			cnt ++;
			v[cnt] = a * s;
			w[cnt] = b * s;
		}
	}

	n = cnt;

	//01背包
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= v[i]; j--)
			f[j] = max(f[j], f[j - v[i]] + w[i]);

	cout << f[m] << endl;

	return 0;
}