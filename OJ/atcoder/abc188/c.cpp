#include <stdio.h>
#include <utility>
#include <vector>
#include <numeric>


//就嗯模拟就行了。。。

int ri() {
    int n;
    scanf("%d", &n);
    return n;
}

int main() {
    int n = ri();
    std::vector<int> a(1 << n);
    for (auto &i : a) i = ri();

    std::vector<int> remaining(1 << n);
    std::iota(remaining.begin(), remaining.end(), 0);

    for (int i = 1; i <= n; i++) {
        std::vector<int> next_remaining;
        for (int j = 0; j < 1 << (n - i); j++) {
            if (a[remaining[j * 2]] > a[remaining[j * 2 + 1]]) next_remaining.push_back(remaining[j * 2]);
            else next_remaining.push_back(remaining[j * 2 + 1]);
        }
        if (i == n) {
            printf("%d\n", 1 + (remaining[0] == next_remaining[0] ? remaining[1] : remaining[0]));
            return 0;
        }
        remaining = next_remaining;
    }

    return 0;
}