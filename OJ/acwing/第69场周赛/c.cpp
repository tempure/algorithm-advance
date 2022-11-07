#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/*
就是求 a - x = a xor x 整数解
结论就是a的二进制表示有k个1，那么答案就是 2^k
因为a为1的二进制位，x放1放0都可以
对于a的二进制表示为0的位，x这位肯定不能放1，如果放1那么a就要像高位借位，导致a被借位的那个1变为0
那么这个1变为0后，不借位之前的a与x xor 那一位恰好相反。答案肯定不相同的。你要相同就得每一个二进制位都相同。
*/

int main() {
    int T;
    cin >> T;

    while (T -- ) {
        int n;
        cin >> n;

        int cnt = 0;
        while (n) cnt += n & 1, n >>= 1;

        cout << (1 << cnt) << endl;
    }

    return 0;
}