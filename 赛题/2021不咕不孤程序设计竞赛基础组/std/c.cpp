#include <iostream>
using namespace std;

int n, a[2010], ans;

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        a[i + n] = a[i];

    for (int cur = 0; cur < n; ++cur)
    {
        bool flag = false;
        for (int i = 0; i < n; ++i)
        {
            if (a[cur + i] < a[ans + i])
                break;
            if (a[cur + i] > a[ans + i])
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            ans = cur;
    }

    for (int i = 0; i < n; ++i)
        cout << a[ans + i] << " ";

    return 0;
}
