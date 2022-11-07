#include<bits/stdc++.h>
using namespace std;

//求根公式
//题目给定 d>=0 如果有解 根一定是>=0 的 简单x1+x2>=0 x1*x2 >=0 推导下就行

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        double d;
        cin >> d;
        double a, b;
        if (d * d - 4 * d < 0) {
            cout << "N" << endl;
        } else {
            cout << "Y" << " ";
            a = (d + sqrt(d * d - 4 * d)) / 2;
            b = (d - sqrt(d * d - 4 * d)) / 2;
            printf("%.10f %.10f\n", a, b);
        }
    }

    return 0;
}