//普通队列
// hh 表示队头，tt表示队尾
int q[N], hh = 0, tt = -1;
// 向队尾插入一个数
q[ ++ tt] = x;
// 从队头弹出一个数
hh ++ ;
// 队头的值
q[hh];
// 判断队列是否为空
if (hh <= tt) {
    //
}

//循环队列
// hh 表示队头，tt表示队尾的后一个位置
int q[N], hh = 0, tt = 0;
// 向队尾插入一个数
q[tt ++ ] = x;
if (tt == N) tt = 0;
// 从队头弹出一个数
hh ++ ;
if (hh == N) hh = 0;
// 队头的值
q[hh];
// 判断队列是否为空
if (hh != tt) {
    //
}

//单调队列
/*
例题:滑动窗口:给定一个大小为n <= 1e6的数组。
有一个大小为k的滑动窗口，它从数组的最左边移动到最右边。
您只能在窗口中看到k个数字。
每次滑动窗口向右移动一个位置。
您的任务是确定滑动窗口位于每个位置时，窗口中的最大值和最小值。
*/
const int N = 1000010;
int n, k;
int a[N], q[N];  //q存储单调队列的下标
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    int hh = 0, tt = 0;
    for (int i = 0; i < n; i++) {
        if (hh <= tt && i - q[hh] + 1 > k) hh++;
        while (hh <= tt && a[q[tt]] >= a[i]) tt--;
        q[++tt] = i; // 需要先加入新的 因为新的可能是最小的
        //窗口完全滑进队列之后才开始判断
        if (i >= k - 1) cout << a[q[hh]] << ' ';
    }
    cout << endl;
    //最大值 修改上边代码即可 大于号改成小于号即可
    hh = 0, tt = -1;
    for (int i = 0; i < n; i++) {
        if (hh <= tt && i - k + 1 > q[hh]) hh++;
        while (hh <= tt && a[q[tt]] <= a[i]) tt--;
        q[++tt] = i; // 需要先加入新的 因为新的可能是最小的
        //窗口完全滑进队列之后才开始判断
        if (i >= k - 1) cout << a[q[hh]] << ' ';
    }
}
