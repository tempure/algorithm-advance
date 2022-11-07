#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main()
{
    int n;
    cin >> n;

    unordered_set<int> hash;
    while (n -- )
    {
        int x;
        cin >> x;
        if (x) hash.insert(x);
    }

    cout << hash.size() << endl;
    return 0;
}