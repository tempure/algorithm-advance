#include <iostream>
using namespace std;

int n, ans[11];
int main()
{

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int cnt = 0, x;
        cin >> x;
        if (x == 0)
            ++ans[1];
        while (x != 0)
        {
            x = x / 10;
            ++cnt;
        }
        ++ans[cnt];
    }
    for (int i = 1; i <= 10; ++i)
    {
        cout << ans[i] << endl;
    }

    return 0;
}
