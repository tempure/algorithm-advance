#include <bits/stdc++.h>
using namespace std;

int main(){
    long long k;
    cin >> k;
    string res = "";
    while(k > 0){
        if(k & 1) res += "2";
        else res += "0";
        k >>= 1;
    }
    reverse(res.begin(), res.end());
    cout << res << endl;
}