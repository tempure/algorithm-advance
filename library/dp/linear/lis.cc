/*
给定一个长为N的数列，求数值严格单递的子序列的长度最长是多少
输入格式
第一行包含整数N。 1<=N<=1000，−1e9<=数列中的数<=1e9
第二行包含N个整数，表示完整序列。
输出格式
输出一个整数，表示最大长度。 暴力O(n^2)
*/
const int N = 1010;
int a[N], f[N];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
    }
    int res = 0;
    for (int i = 1; i <= n; i++) res = max(res, f[i]);
    cout  << res << endl;
    return 0;
}
/*
O(n * logn)做法 1<=N<=100000
*/
const int N = 1e5 + 10;
int n, a[N];
int q[N];  //储存上升子序列 结尾的最小值
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    int len = 0;  //q元素个数
    q[0] = -2e9;  //边界
    for (int i = 0 ; i < n; i++) {
        int l = 0, r = len;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (q[mid] < a[i]) l = mid;
            else r = mid - 1;
        }
        len = max(len, r + 1);
        q[r + 1] = a[i];
    }
    cout << len << endl;
    return 0;
}
/*
Dilworth定理 例题：拦截导弹
输入格式:共一行，输入导弹依次飞来的高度。
输出格式
第一行包含一个整数，表示最多能拦截的导弹数。
第二行包含一个整数，表示要拦截所有导弹最少要配备的系统数。
*/
const int N = 1010;
int f[N];
int rf[N];
vector<int> a;
/*
Dilworth定理：
    “能覆盖整个序列的最少的不上升子序列的个数”等价于“该序列的最长上升子序列长度”
    同理即有：
    “能覆盖整个序列的最少的不下降子序列的个数”等价于“该序列的最长下降子序列长度”
*/
int main() {
    int x;
    while (cin >> x) {
        a.push_back(x);
    }
    for (int i = a.size() - 1; i >= 0; i--) {
        f[i] = 1;
        for (int j = a.size() - 1; j > i; j--)
            if (a[j] <= a[i]) f[i] = max(f[i], f[j] + 1); //注意相等也可以拦截
    }
    int res1 = 0;
    for (int i = 0; i < a.size(); i++) res1 = max(res1, f[i]);
    int res2 = 0;
    for (int i = 0; i < a.size(); i++) {
        rf[i] = 1;
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) rf[i] = max(rf[i], rf[j] + 1);

    }
    for (int i = 0; i < a.size(); i++) res2 = max(res2, rf[i]);
    cout << res1 << endl;
    cout << res2 << endl;
    return 0;
}
/*最大上升子序列和
一个数的序列 bi，当 b1<b2<…<bS 的时候，我们称这个序列是上升的。
对于给定的一个序列(a1,a2,…,aN)，我们可以得到一些上升的子序列(ai1,ai2,…,aiK)，这里1≤i1<i2<…<iK≤N。
比如，对于序列(1,7,3,5,9,4,8)，有它的一些上升子序列，如(1,7),(3,4,8)等等。
这些子序列中和最大为18，为子序列(1,3,5,9)的和。
你的任务，就是对于给定的序列，求出最大上升子序列和。
注意，最长的上升子序列的和不一定是最大的，比如序列(100,1,2,3)的最大上升子序列和为100，而最长上升子序列为(1,2,3)。
输入格式:输入的第一行是序列的长度N。
第二行给出序列中的N个整数，这些整数的取值范围都在0到10000(可能重复)。
输出格式:输出一个整数，表示最大上升子序列和。
*/
typedef pair<int, int> pii;
const int N = 1010;
vector<pii> a;
//用第一关键字保存元素的值
//第二关键字维护上升子序列的最大值
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back({x, 0});
    }
    for (int i = 0 ; i < n; i++) {
        a[i].second = a[i].first;
        for (int j = 0 ; j < i; j++)
            if (a[j].first < a[i].first) a[i].second = max(a[i].second, a[j].second + a[i].first);
    }
    int res = 0;
    for (int i = 0; i < n; i++) res = max(res, a[i].second);
    cout << res << endl;
    return 0;
}