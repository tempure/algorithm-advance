#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//减2次可以抵消掉第一次的
//就是看是否k是某2个元素的差

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, a;
        cin >> n >> a;
        vector<int> v(n);
        for (int& x : v) cin >> x;
        bool ans = false;
        if (n == 1) ans = (v[0] == a);
        else {
            sort(v.begin(), v.end());
            int i = 0;
            int j = 1;
            while (j < n and i < n) {
                if (v[i] + abs(a) == v[j]) {
                    ans = true;
                    break;
                }
                else if (v[i] + abs(a) < v[j]) ++i;
                else ++j;
            }
        }
        cout << (ans ? "YES" : "NO") << '\n';
    }
}