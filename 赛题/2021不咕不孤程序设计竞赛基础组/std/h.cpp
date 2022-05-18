#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

int n;
double a[30][30];
double ans = 1;

void print()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%.2lf ", a[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%lf", &a[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            a[i][j] /= a[i][i];
        }
        ans *= a[i][i];
        a[i][i] = 1;
        for (int j = i + 1; j <= n; j++)
        {
            for (int k = i + 1; k <= n; k++)
            {
                a[j][k] -= a[i][k] * a[j][i];
            }
            a[j][i] = 0;
        }
        // print();
    }
    printf("%.0lf", ans);
    return 0;
}
