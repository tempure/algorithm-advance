#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;

int main()
{
    cin >> n;

    int l = 0, r = 0;
    while (n -- )
    {
        int x, y;
        cin >> x >> y;
        if (x < 0) l ++ ;
        else r ++ ;
    }

    if (l <= 1 || r <= 1) puts("Yes");
    else puts("No");

    return 0;
}