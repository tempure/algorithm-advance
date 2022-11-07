#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i ++ )
    {
        if (s[i] > '4' && !(!i && s[i] == '9'))
            cout << 9 - (s[i] - '0');
        else
            cout << s[i];
    }

    return 0;
}