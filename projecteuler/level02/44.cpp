#include<bits/stdc++.h>
using namespace std;

//暴力
//试探找前3000项求答案
//证明...不太会

//ans = 5482660

int num[10001];
int occur[40000000];

int main() {
    for (int i = 1; i <= 3000; i++)   num[i] = i * (3 * i - 1) / 2, occur[num[i]] = 1;
    int ans = 1 << 30;
    for (int i = 1; i <= 3000; i++) {
        for (int j = 1; j < i; j++) {
            if (occur[num[i] + num[j]] && occur[num[i] - num[j]]) {
                ans = min(ans, num[i] - num[j]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}