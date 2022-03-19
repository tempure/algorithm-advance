#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int res = 0;
    for (int i = 1; i <= n; i ++ )
        for (int j = i; j <= n; j ++ )
            for (int k = j; k <= n; k ++ )
                if ((i ^ j ^ k) == 0 && i + j > k)
                    res ++ ;
    cout << res << endl;
    return 0;
}