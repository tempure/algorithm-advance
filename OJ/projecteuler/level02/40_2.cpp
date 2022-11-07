#include<bits/stdc++.h>
using namespace std;

int tot[10], num[10];

// faster solution
// https://blog.csdn.net/pfccWang/article/details/78106624

int search(int aim, int l, int r) {
    int mid = (l + r) / 2;
    int len = 0;
    while (mid) {mid /= 10; len++;}
    mid = (l + r) / 2;
    if ((mid - num[len - 1])*len + tot[len - 1] - len >= aim)
        return search(aim, l, mid);
    else if ((mid - num[len - 1])*len + tot[len - 1] >= aim) {
        int diff = (mid - num[len - 1]) * len + tot[len - 1] - aim;
        while (diff) {
            diff--;
            mid /= 10;
        }
        return mid % 10;
    }
    else
        return search(aim, mid + 1, r);
}

int main() {
    tot[1] = 9; num[1] = 9; num[0] = 0;
    for (int i = 2; i <= 7; i++) {
        num[i] = (num[i - 1]) * 10 + 9;
        tot[i] = tot[i - 1] + i * (num[i] - num[i - 1]);
    }
    int ans = 1;
    for (int x = 1, i = 1; i <= 7; i++) {
        ans *= search(x, 1, 1000000);
        x *= 10;
    }
    cout << ans << endl;
    return 0;
}