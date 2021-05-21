#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<int> > pq;

int main() {
    int n;
    cin >> n;
    while (n --) {
        int x; cin >> x;
        pq.push(x);
    }

    int res = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        res += a + b;
        pq.push(a + b);
    }

    cout << res << endl;

    return 0;
}