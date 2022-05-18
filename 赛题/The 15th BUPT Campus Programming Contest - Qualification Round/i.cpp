#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int n;

int main() {
    cin >> n;
    int a, b;
    while (n--) {
        scanf("%d", &a);
        if (a <= 0) {
            printf("0\n");
        }
        else {
            scanf("+%d", &b);
            printf("%d\n", a + b * 20);
        }
    }
    return 0;
}