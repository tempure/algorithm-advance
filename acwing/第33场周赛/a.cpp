#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int cnt4 = 0, cnt7 = 0;
    for (auto c : s) {
        if (c == '4') cnt4++;
        if (c == '7') cnt7++;
    }
    if (cnt4 + cnt7 == 4 || cnt4 + cnt7 == 7) puts("YES");
    else puts("NO");

    return 0;
}
