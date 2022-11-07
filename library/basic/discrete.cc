//离散化模板
vector<int> alls; // 存储所有待离散化的值
sort(alls.begin(), alls.end()); // 将所有值排序
// 去掉重复元素
alls.erase(unique(alls.begin(), alls.end()), alls.end());
// 二分求出x对应的离散化的值
int find(int x) { // 找到第一个大于等于x的位置
    int l = 0, r = alls.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1; // 映射到1, 2, ...n
}
/*
    例题:区间和
    假定有一个无限长的数轴，数轴上每个坐标上的数都是0。
    现在，首先进行 n 次操作，每次操作将某一位置x上的数加c
    接下来，进行 m 次询问，每个询问包含两个整数l和r，你需要求出在区间[l, r]之间的所有数的和。
    −1e9 <= x <= 1e9, 1 <= n, m<= 1e5
    −1e9<=l<=r<=1e9, −10000<=c<=10000
*/
typedef pair<int, int> pii;
const int N = 300010; //区间lr都加入后数据范围三倍 开30w
vector<pii> add, query;
vector<int> alls;
int n, m;
int a[N], s[N];
int find(int x) {
    int l = 0, r = alls.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if ( alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, c;
        cin >> x >> c;
        add.push_back({x, c});
        alls.push_back(x); //保存操作的下标
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        query.push_back({l , r});
        alls.push_back(l); alls.push_back(r);
    }
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());
    for (auto item : add) {
        int x = find(item.first);
        a[x] += item.second;
    }
    for (int i = 1; i <= alls.size(); i++)
        s[i] = s[i - 1] + a[i];
    for (auto item : query) {
        int l = find(item.first), r = find(item.second);
        int res = s[r] - s[l - 1];
        cout << res << endl;
    }
    return 0;
}