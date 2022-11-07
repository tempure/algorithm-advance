#include <bits/stdc++.h>
using namespace std;

//https://codeforces.com/problemset/problem/1030/C
//https://codeforces.com/blog/entry/62013

void solve() {
	int n;
	string s;
	cin >> n >> s;
	int sum = 0;
	for (int i = 0; i < n - 1; ++i) { // n -1 至少分为2部分
		sum += s[i] - '0';

		bool ok = true;
		int pos = i + 1;
		int sum2 = 0;
		while (pos < n) {
			sum2 = s[pos++] - '0';
			while (pos < n && sum2 + s[pos] - '0' <= sum) {
				sum2 += s[pos] - '0';
				++pos;
			}
			if (sum2 != sum) ok = false;
		}

		if (sum2 != sum) ok = false;
		if (ok) {
			puts("YES");
			return;
		}
	}

	puts("NO");
}

int main() {
	int t = 1;
	// cin >> t;
	while (t --) solve();
	return 0;
}