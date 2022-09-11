#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//把从左边出的和从右边出的加起来就好了

string s;
int n, m;
int main() {
    cin >> n;
    cin >> s;

    for (int i = 0; i < n && s[i] == '<'; i ++ ) m ++ ;
    for (int i = n - 1; i >= 0 && s[i] == '>'; i -- ) m ++ ;
    cout << m;
}