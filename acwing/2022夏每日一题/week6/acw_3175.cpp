#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int arr[N];
int seq[N];//存储逆序数列
int n, res;

//https://www.acwing.com/problem/content/3718/
//暴力

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 1; i <= n; i++) {
        int t = 0;
        int j = i - 1;
        while (j >= 1)
            if (arr[j--] > arr[i])
                t++;
        seq[arr[i]] = t;
        res += t; //res为逆序对总数
    }
    for (int i = 1; i <= n; i++)
        cout << seq[i] << " ";
    cout << endl << res;
    return 0;
}