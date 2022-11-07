#include <iostream>
#include <algorithm>

using namespace std;

int n, k, q;
int ans[5010][5010];
bool p[5010];
pair<int, int> b[20010];

int main()
{
    cin >> n >> k >> q;
    for (int i = 1; i <= k; i++)
    {
        int l, r, id;
        cin >> id >> l >> r;
        b[i * 2 - 1].first = l;
        b[i * 2].first = r;
        b[i * 2 - 1].second = id;
        b[i * 2].second = id;
    }
    for (int i = 1; i <= q; i++)
    {
        int t;
        cin >> t;
        b[k * 2 + i].first = t;
        b[k * 2 + i].second = i + n;
    }
    sort(b + 1, b + k * 2 + q + 1);
    for (int i = 1; i <= k * 2 + q; i++)
    {
        if (b[i].second <= n)
        {
            p[b[i].second] = !p[b[i].second];
        }
        else
        {
            for (int j = 1; j <= n; j++)
            {
                if (!p[j])
                {
                    ans[b[i].second - n][++ans[b[i].second - n][0]] = j;
                }
            }
        }
    }
    for (int i = 1; i <= q; i++)
    {
        for (int j = 1; j <= ans[i][0]; j++)
        {
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
