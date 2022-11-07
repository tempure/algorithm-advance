/*
    例题：给定 n 个区间 [li,ri]，要求合并所有有交集的区间。
    注意如果在端点处相交，也算有交集。
    输出合并完成后的区间个数。
    例如：[1,3]和[2,6]可以合并为一个区间[1,6]。
    1 <= n <= 100000, −1e9 <= li <= ri <= 1e9
*/
typedef pair<int, int> PII;
const int N = 100010;
int n;
vector<PII> segs;
void merge(vector<PII> &segs) {
    vector<PII> res;
    sort(segs.begin(), segs.end());
    int st  = -2e9, ed = -2e9; //左右边界从无限远处来开始维护
    //注意维护的逻辑是先用上一个区间和新的区间比较 然后压入上一个区间 新的区间又和下一个比较 最后要把最后一个压进去
    for (auto seg : segs) {
        if (ed < seg.first) {
            if (st != -2e9) res.push_back({st, ed});  //第一个区间维护 不要加进去初始的最小的那个
            st = seg.first, ed = seg.second; //第一次循环就是从第一个区间开始维护
        }
        else ed = max(ed, seg.second);
    }
    if (st != -2e9) res.push_back({st, ed}); //最后一个区间，同时判断是否为空区间
    segs = res;
}
int main(int argc, char const *argv[]) {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        segs.push_back({l, r});
    }
    merge(segs); printf("%d", segs.size());
    return 0;
}