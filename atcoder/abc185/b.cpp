#include <bits/stdc++.h>

//极度无聊的模拟题。。。没啥意思。。。

int ri() {
    int n;
    scanf("%d", &n);
    return n;
}

int main() {
    int n = ri();
    int m = ri();
    int t = ri();
    int last_time = 0;
    int cur = n;
    bool res = true;
    for (int i = 0; i <= m; i++) {
        int a = i < m ? ri() : t;
        int b = i < m ? ri() : t;
        cur -= a - last_time;
        if (cur <= 0) res = false;
        cur = std::min(n, cur + b - a);
        last_time = b;
    }
    puts(res ? "Yes" : "No");
    return 0;
}