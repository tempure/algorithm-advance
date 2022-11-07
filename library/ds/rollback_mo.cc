/*JOI2013《历史研究》：给定长度为N的序列，Q个区间询问。求[L,R]内某元素出现次数乘该元素值的最大值
1<=N<=1e5,1<=Q<=1e5,1<=Xi<=1e9
只加不减的回滚莫队：询问的排序原则依然是块外左端点，块内按照右端点排序，从前往后处理所有询问
1.对于左右端点都在同一个块内的询问，直接暴力，每次刷新cnt[]来求，求完之后清空cnt[]即可
因为暴力求解询问可以理解是“一次性”的，每次及时得到答案，然后求下一个左右端点都在块内的询问
2.对于左右端点不在一个区间内的询问：左半截在块内的直接一次性暴力，右边用右指针扫add即可
cnt[]此时只会保留后面横跨部分询问的区间的信息，用来更新下一个块的后面递增的询问区间部分
而前半部分在块内的由于是一次性的暴力，每次add完之后删除即可
总结一下就是暴力求解的部分要恢复cnt[]，右指针每个块线性递增扫描不用恢复cnt[]，复杂度O(N*sqrt(N))*/
typedef long long ll;
const int N = 100010;
int n, m, len;
int w[N], cnt[N];
ll ans[N];
vector<int> nums; //离散化
struct Query {
    int id, l, r;
} q[N];
int get(int x) {
    return x / len;
}
bool cmp(const Query& a, const Query& b) {
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}
void add(int x, ll &res) {
    cnt[x] ++;
    res = max(res, (ll)cnt[x] * nums[x]);
}
int main() {
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    //离散化
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        nums.push_back(w[i]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 1; i <= n; i++)
        w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    sort(q, q + m, cmp);
    for (int x = 0; x < m;) {//处理所有询问
        int y = x;
        while (y < m && get(q[y].l) ==  get(q[x].l)) y ++;
        int right = get(q[x].l) * len + len - 1;
        //暴力求左右端点都在当前块内的询问
        while (x < y && q[x].r <= right) {
            ll res = 0;
            int id = q[x].id, l = q[x].l, r = q[x].r;
            for (int k = l; k <= r; k++) add(w[k], res);
            ans[id] = res;
            //清空临时存储暴力结果的cnt
            for (int k = l; k <= r; k++) cnt[w[k]] --;
            x ++;
        }
        //求出右端点超过当前块尾但是左端点在当前块内的所有询问
        ll res = 0;
        int i = right, j = right + 1;
        while (x < y) {
            int id = q[x].id, l = q[x].l, r = q[x].r;
            while (i < r) add(w[++i], res); //右边块的后半截
            ll backup = res; //只需要保存这后半截的res
            while (j > l) add(w[--j], res); //暴力前半截处于前一个块的部分
            ans[id] = res;
            //清空前半截的暴力部分cnt[]
            while (j < right + 1) cnt[w[j++]]--;
            res = backup;
            x++;
        }
        //清空cnt[] 开始计算左端点在下一个块中开始的询问
        //因为当前后半截和后面左端点在右边块的询问会有重合部分
        //暴力计算是不用cnt[]更新下一个询问的,所以必须清空
        memset(cnt, 0, sizeof cnt);
    }
    for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);
    return 0;
}