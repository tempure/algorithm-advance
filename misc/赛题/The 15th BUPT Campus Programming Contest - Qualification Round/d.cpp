#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;

const int N = 105;

int n, m, tot;
long long s;
long long a[N], b[N];

bool cmp(int c, int d) {
    return c > d;
}

int main() {
    int i, j, k;
    long long x;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++) {
            scanf("%lld", &x);
            s += x;
            if (x == 0)
                tot++;
            if (x > a[i])
                a[i] = x;
            if (x > b[j])
                b[j] = x;
        }
    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + m + 1, cmp);
    for (i = 1, j = 1; i <= n && j <= m; i++) {
        if (a[i] == b[j]) {
            j++;
            s -= a[i];
            k++;
        }
        else {
            if (a[i] < b[j]) {
                while (j <= m && a[i] < b[j]) {
                    s -= b[j];
                    j++;
                    k++;
                }
            }
            else {
                //printf("%d %d\n",i,j);
                s -= a[i];
                k++;
            }
        }
    }
    while (i <= n) {
        s -= a[i];
        i++;
        k++;
    }
    while (j <= m) {
        s -= b[j];
        j++;
        k++;
    }
    //cout<<s<<endl<<k<<endl<<tot<<endl;
    cout << s - n*m + k + tot;
    return 0;
}