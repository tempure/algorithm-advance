#include <iostream>
using namespace std;

/*
直接开个左右标记，累计相对位置就行了
*/

const int N = 2e5;
int p[N];

int main() {
	int n; cin >> n;
	int l = 0, r = -1; //初始区间为空
	while (n --) {
		char op;
		int t;
		cin >> op >> t;
		if (op == 'L') p[t] = --l;
		else if (op == 'R') p[t] = ++r;
		else cout << min(p[t] - l, r - p[t]) << endl;
	}

	return 0;
}