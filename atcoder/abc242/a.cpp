#include<bits/stdc++.h>

using namespace std;

int main() {
    int a, b, c, x;
    cin >> a >> b >> c >> x;

    if (x <= a) {printf("%.12lf\n", 1.0);}
    else if (x <= b) {
        double res = c;
        res /= (b - a);
        printf("%.12lf\n", res);
    }
    else {
        printf("%.12lf\n", 0.0);
    }
    return 0;
}