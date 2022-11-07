#include<bits/stdc++.h>
using namespace std;

int main() {
	int N, K; cin >> N >> K;
	vector<int> P(N);
	for (int i = 0; i < N; i++) cin >> P[i];
	priority_queue<int, vector<int>, greater<int> > que;
	for (int i = 0; i < K; i++) que.push(P[i]);
	cout << que.top() << endl;
	for (int i = K; i < N; i++) {
		if (que.top() < P[i]) {
			que.pop();
			que.push(P[i]);
		}
		cout << que.top() << endl;
	}
}