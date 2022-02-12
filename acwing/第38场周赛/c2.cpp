#include <iostream>
#include <cstring>
#include <algorithm>

//https://www.acwing.com/activity/content/code/content/2575738/

using namespace std;

const int N = 110;

int n;
char d[N];

int main() {
    cin >> n >> d;
    int sum = 0;
    for (int i = 0; i < n; i ++ ) {
        d[i] -= '0';
        sum += d[i];
    }
    for (int k = 2; k <= n; k ++ ) //枚举端数
        if (sum % k == 0) {
            bool flag = true;
            int s = sum / k;
            for (int j = 0, t = 0; j < n; j ++ ) {
                t += d[j];
                if (t > s) {
                    flag = false;
                    break;
                }
                else if (t == s) {
                    t = 0;
                }
            }
            if (flag) {
                puts("YES");
                return 0;
            }
        }
    puts("NO");
    return 0;
}