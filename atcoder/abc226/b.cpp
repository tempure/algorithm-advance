#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    getchar();
    set<vector<int>> S;
    while (n --) {
        string s;
        getline(cin, s);
        stringstream ssin(s);
        int p = 0;
        vector<int> temp;
        while (ssin >> p) {
            temp.push_back(p);
        }
        S.insert(temp);
    }
    cout << S.size() << endl;
    return 0;
}