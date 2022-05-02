//https://www.cnblogs.com/xsl19/p/12824379.html
//https://blog.csdn.net/qq_42886072/article/details/105910432
//暴力DFS
#include<cstdio>
#include<string>
#include<cstdlib>
#include<iostream>
using namespace std;
const int N = 1e5 + 10;

int n;
char ans[N];
string str[N];

void dfs(int i, int a, int b, int c) {
    if (i > n) {
        puts("Yes");
        for (int i = 1; i <= n; i++) putchar(ans[i]), puts("");
        exit(0);
    }
    if (str[i] == "AB") {
        if (a) ans[i] = 'B', dfs(i + 1, a - 1, b + 1, c);
        if (b) ans[i] = 'A', dfs(i + 1, a + 1, b - 1, c);
    }
    else if (str[i] == "AC") {
        if (a) ans[i] = 'C', dfs(i + 1, a - 1, b, c + 1);
        if (c) ans[i] = 'A', dfs(i + 1, a + 1, b, c - 1);
    }
    else {
        if (b) ans[i] = 'C', dfs(i + 1, a, b - 1, c + 1);
        if (c) ans[i] = 'B', dfs(i + 1, a, b + 1, c - 1);
    }
}

int main() {
    scanf("%d", &n); int a, b, c; scanf("%d %d %d", &a, &b, &c);
    for (int i = 1; i <= n; i++) cin >> str[i];
    dfs(1, a, b, c); puts("No"); exit(0);
}
