#include<bits/stdc++.h>
using namespace std;

//ans = 162
//先求出 前100个  triangle number
//然后暴力判断就行

int main() {
    int num[10000];
    for (int i = 1; i <= 100; i++)    num[i * (i + 1) / 2] = 1;
    freopen("p042_words.txt", "r", stdin);
    string tmp;
    int ans = 0;
    cin >> tmp;
    for (int i = 1, sum = 0; tmp[i]; i += 3, sum = 0) {
        for (; tmp[i] != 34; i++)   sum += tmp[i] - 'A' + 1;
        if (num[sum])    ans++;
    }
    cout << ans << endl;
    return 0;
}