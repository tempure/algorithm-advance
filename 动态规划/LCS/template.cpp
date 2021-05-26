//最长公共子序列 非连续
#include <iostream>
using namespace std;

//f[i][j] A串的前i个字母和B串的前j个字母的LCS长度
//集合划分为4部分：对于A串的当前最后一个字母和B串的最后一个字母
//都不选 f[i][j] = f[i-1][j-1]
//选a不选b f[i][j] = f[i][j-1]
//选b不选a f[i][j] = f[i-1][j]
//最后一个字母相同 都选 f[i][j] = f[i-1][j-1] + 1

//这些集合有重复，但是目的是求最大，即使重复也不影响最值，但是如果是求的是数量，需要DP减去重复集合的元素（容斥）
//注意到第一种选法的集合完全包含在2，3中，所以不用特殊计算

const int N = 1010;
int f[N][N];
char a[N], b[N];

int main() {
	int n, m;
	cin >> n >> m;
	cin >> a + 1 >> b + 1;

	for (int i =  1; i <= n; i++)
		for (int j = 1; j <= m; j ++) {
			f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			if (a[i] == b[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
		}
	cout << f[n][m] << endl;

	return 0;
}