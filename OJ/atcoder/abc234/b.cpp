#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int x[N], y[N];

int main(){
    int n;
    cin >> n;
    int res = -1;
    for(int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    for(int i = 0; i<n; i++)
        for(int j = i + 1;j < n; j++)
            res = max(res, (x[i]-x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
    printf("%.8lf\n", sqrt(1.0*res));
    return 0;
}