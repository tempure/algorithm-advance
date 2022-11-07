#include <iostream>
#include <string>
using namespace std;

//更复杂问题可以规约为逆序对的奇偶性排列
//https://atcoder.jp/contests/abc244/editorial/3616

bool sign(string S) {
    return S == "R G B" || S == "G B R" || S == "B R G";
}
int main() {
    string S, T;
    getline(cin, S);
    getline(cin, T);
    if (sign(S) == sign(T)) cout << "Yes" << endl;
    else cout << "No" << endl;
}