#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
const int N = 2010;
int n, x, y, t[2100];

//https://blog.csdn.net/qq_45288870/article/details/105178735

int main() {
    cin >> n >> x >> y;
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            t[min(j - i, abs(j - y) + abs(x - i) + 1)]++;
    for (int i = 1; i < n; i++) cout << t[i] << endl;
    return 0;
}