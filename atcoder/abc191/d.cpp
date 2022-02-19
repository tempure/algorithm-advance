#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<string.h>
#include<cmath>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define NDEBUG
#define eprintf(...) do {} while (0)
#endif
#include<cassert>

using namespace std;

typedef long long LL;
typedef vector<int> VI;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define EACH(i,c) for(__typeof((c).begin()) i=(c).begin(),i##_end=(c).end();i!=i##_end;++i)

template<class T> inline void amin(T &x, const T &y) { if (y < x) x = y; }
template<class T> inline void amax(T &x, const T &y) { if (x < y) x = y; }
#define rprintf(fmt, begin, end) do { const auto end_rp = (end); auto it_rp = (begin); for (bool sp_rp=0; it_rp!=end_rp; ++it_rp) { if (sp_rp) putchar(' '); else sp_rp = true; printf(fmt, *it_rp); } putchar('\n'); } while(0)

LL read() {
    double x;
    scanf("%lf", &x);
    return llround(x * 10000);
}

LL sq(LL x) { return x * x; }

LL X, Y, R;

void MAIN() {
    X = read();
    Y = read();
    R = read();

    LL ans = 0;

    LL RR = sq(R);
    LL high = Y + 1;
    LL low = Y - 1;
    LL pos = X - R;
    while (pos % 10000) pos++;
    while (high % 10000) high++;
    while (low % 10000) low--;

    for (; pos <= X + R; pos += 10000) {
        LL A = sq(pos - X);
        while (A + sq(high - Y) > RR) high -= 10000;
        while (high <= Y || A + sq(high - Y) <= RR) high += 10000;

        while (A + sq(low - Y) > RR) low += 10000;
        while (low >= Y || A + sq(low - Y) <= RR) low -= 10000;

        LL add = (high - low) / 10000 - 1;
        if (add > 0) {
            ans += add;
        }
    }

    printf("%lld\n", ans);
    // eprintf("%lld %lld %lld\n", X, Y, R);
}

int main() {
    int TC = 1;
//    scanf("%d", &TC);
    REP (tc, TC) MAIN();
    return 0;
}

