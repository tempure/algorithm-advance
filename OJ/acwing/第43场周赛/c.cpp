#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 400010; //s[i] -t , s[i] 放二倍的元素个数

//离散化+树状数组

int n;
LL m;
LL s[N], xs[N], cnt;
int tr[N];

int get(LL x)
{
    int l = 1, r = cnt;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (xs[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r;
}

int lowbit(int x)
{
    return x & -x;
}

void add(int x, int v)
{
    for (int i = x; i < N; i += lowbit(i))
        tr[i] += v;
}

int query(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += tr[i];
    return res;
}

int main()
{
    scanf("%d%lld", &n, &m);
    xs[ ++ cnt] = 0, xs[ ++ cnt] = -m;
    for (int i = 1; i <= n; i ++ )
    {
        int x;
        scanf("%d", &x);
        s[i] = s[i - 1] + x;
        xs[ ++ cnt] = s[i], xs[ ++ cnt] = s[i] - m;
    }

    sort(xs + 1, xs + cnt + 1);
    cnt = unique(xs + 1, xs + cnt + 1) - xs - 1;

    LL res = 0;
    add(get(0), 1);
    for (int i = 1; i <= n; i ++ ) //枚举前缀和的右端点 j...i  s[i] - s[j-1] < t -> s[j-1] > s[i]-t;
    {
        res += i - query(get(s[i] - m)); //当前一共加了i个元素，比s[i]-t小于等于的，query之后减去就是大的
        add(get(s[i]), 1);
    }
    printf("%lld\n", res);
    return 0;
}