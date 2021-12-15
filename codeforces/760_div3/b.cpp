#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,l,r) for(int i=(l);i>=(r);i--)
#define pb push_back
#define fir first
#define sec second
#define SZ(x) (int(x.size()))
#define pii pair<int,int>
inline int read() {
    int x = 0, f = 0; char ch = getchar();
    while (!isdigit(ch))f |= ch == '-', ch = getchar();
    while (isdigit(ch))x = 10 * x + ch - '0', ch = getchar();
    return f ? -x : x;
}
template<class T>void print(T x) {
    if (x < 0)putchar('-'), x = -x;
    if (x >= 10)print(x / 10);
    putchar(x % 10 + '0');
}
template<class T>void print(T x, char let) {print(x), putchar(let);}
template<class T1, class T2>void ckmin(T1&x, T2 y) {if (x > y)x = y;}
template<class T1, class T2>void ckmax(T1&x, T2 y) {if (x < y)x = y;}

const int N = 205;
char tmp[N][5];
int n;

//https://codeforces.com/contest/1618/submission/139229313

//呃呃 这题就纯恶心人 有啥意义

void solve() {
    n = read();
    rep(i, 1, n - 2) {
        scanf("%s", tmp[i]);
    }
    rep(i, 2, n - 2) {
        if (tmp[i - 1][1] != tmp[i][0]) {
            rep(j, 1, i - 1)putchar(tmp[j][0]);
            putchar(tmp[i - 1][1]);
            putchar(tmp[i][0]);
            rep(j, i, n - 2)putchar(tmp[j][1]);
            putchar('\n');
            return;
        }
    }
    rep(i, 1, n - 2)putchar(tmp[i][0]);
    putchar(tmp[n - 2][1]);
    putchar('a');
    putchar('\n');
}

int main() {
    int T = read();
    while (T--)solve();
    return 0;
}