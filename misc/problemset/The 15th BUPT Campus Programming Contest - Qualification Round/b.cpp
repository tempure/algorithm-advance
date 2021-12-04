#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

//const int N=1005;

//int a[N][N];
int n, m;

int main() {
    int x, y, i, j;
    cin >> n >> m;
    if (n % 2 == 0 && m % 2 == 0) {
        printf("NO");
        return 0;
    }
    else {
        printf("YES\n");
        if (n == 2) {
            x = 2;
            y = 1;
            i = -1;
            printf("%d %d\n", x, y);
            y++;
            while (!(x == 1 && y == m)) {
                printf("%d %d\n", x, y);
                x += i;
                printf("%d %d\n", x, y);
                i *= -1;
                y++;
            }
            printf("%d %d\n", x, y);
            return 0;
        }
        if (m == 2) {
            x = 1;
            y = 2;
            i = -1;
            printf("%d %d\n", x, y);
            x++;
            while (!(x == n && y == 1)) {
                printf("%d %d\n", x, y);
                y += i;
                printf("%d %d\n", x, y);
                i *= -1;
                x++;
            }
            printf("%d %d\n", x, y);
            return 0;
        }
        //a[1][1]=a[n][m]=1;
        if (n < m) {
            x = 1;
            y = 2;
            i = 1;
            //return 0;
            while (!(x == n && y == m - 1)) {
                printf("%d %d\n", x, y);
                if (y < m && y > 1) {
                    y += i;
                }
                else {
                    x++;
                    printf("%d %d\n", x, y);
                    i *= -1;
                    y += i;
                }
            }
            printf("%d %d\n", x, y);
        }
        else {
            x = 2;
            y = 1;
            i = 1;
            while (!(x == n - 1 && y == m)) {
                printf("%d %d\n", x, y);
                if (x < n && x > 1) {
                    x += i;
                }
                else {
                    y++;
                    printf("%d %d\n", x, y);
                    i *= -1;
                    x += i;
                }
            }
            printf("%d %d\n", x, y);
        }
    }
    return 0;
}

