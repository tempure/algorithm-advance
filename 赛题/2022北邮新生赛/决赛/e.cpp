#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n;
    cin >> n;
    bool flag = false;
    int res = 0;
    if (n > 0) {
        // n = abs(n);
        // if (n < 0) flag = true;
        if (n % 2 == 0) {
            long long t = n / 3;
            if (t % 2 == 0) t++;
            while (t * 3 + 1 < n) t += 2;
            cout << (n + 1) / 2 + (n - t + 1) / 2  << endl;
        }
        else {
            long long t = n / 3;
            if (t % 2 == 0) t++;
            while (t * 3 + 1 < n) t += 2;
            res = (n + 1) / 2 + (n - t + 1) / 2 + 1;
            cout << (n + 1) / 2 + (n - t + 1) / 2 + 1 << endl;
        }
    }
    else if (n == 0) {
        cout << 0 << endl;
    }
    else {
        n = abs(n);
        if (n % 2 == 0) {
            long long t = n / 3;
            if (t % 2 == 0) t++;
            while (t * 3 + 1 < n) t += 2;
            cout << (n + 1) / 2 + (n - t + 1) / 2  << endl;
        }
        else {
            long long t = n / 3;
            if (t % 2 == 0) t++;
            while (t * 3 + 1 < n) t += 2;
            // res = (n + 1) / 2 + (n - t + 1) / 2 + 1;
            cout << (n + 1) / 2 + (n - t + 1) / 2 + 1 - 2 << endl;
        }
    }    // else {
    //     // n = abs(n);
    //     if (n % 2 == 0) {
    //         long long t = n / 3;
    //         if (t % 2 == 0) t++;
    //         while (t * 3 + 1 > n) t -= 2;
    //         cout << (-n + 1) / 2 + (t - n + 1) / 2  << endl;
    //     }
    //     else {
    //         long long t = n / 3;
    //         if (t % 2 == 0) t++;
    //         while (t * 3 + 1 > n) t -= 2;
    //         cout << -n / 2 + (t - n + 1) / 2 << endl;
    //     }
    // }
}

int main() {
    int t;
    cin >> t;
    while (t -- ) solve();
}
