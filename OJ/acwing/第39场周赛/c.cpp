#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int n;
int p[N];
int id[26];
char str[55];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) p[i] = i;

    int res = n;
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%s", str);
        for (int j = 0; str[j]; j ++ )
        {
            int c = str[j] - 'a';
            if (id[c])
            {
                if (find(i) != find(id[c]))
                {
                    p[find(i)] = find(id[c]);
                    res -- ;
                }
            }
            else id[c] = i;
        }
    }

    printf("%d\n", res);
    return 0;
}