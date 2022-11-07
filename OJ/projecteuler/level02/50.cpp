#include<bits/stdc++.h>
using namespace std;

//连续质数的话那直接暴力就行了
//枚举每个质数为起点，一直往后扫，然后更新答案

const int n = 1000000;
int num[n + 1], prime[n + 1], cnt;

int main() {
    for (int i = 2; i <= n; i++) {
        if (!num[i])    prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            num[i * prime[j]] = 1;
        }
    }
    int maxx = 0, ans;
    for (int i = 1; i <= cnt; i++) {
        int sum = 0;
        for (int j = 0; sum < n && j + i <= cnt; j++) {
            sum += prime[i + j];
            if (maxx < j && sum < n && num[sum] == 0) {
                maxx = j; ans = sum;
            }
        }
    }
    cout << ans << endl;
    return 0;
}