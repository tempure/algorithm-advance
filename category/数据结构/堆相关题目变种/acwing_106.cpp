#include <bits/stdc++.h>
using namespace std;


/*
对顶堆动态维护中位数，单词操作O(log)

左边开一个小根堆，右边开一个大根堆
1.左边所有元素都大于右边所有元素
2.右边堆大小>=左边+1，此时右边堆顶就是中位数

可以看成是一个🥾|🥿的形状, 中间分割处是2个堆的堆顶
维护:假设当前插入x，如果右边为空，或者x小于右边堆顶，那么插入右边,为空插入是为了满足初始右边个数大，否则插入左边
按照大小插入之后重新调整2个堆的大小，如果右边大于左边+1大小，那么右边堆顶插入到左边，右堆顶弹出
如果左边元素个数大于右边，那么左堆顶弹出，插入右边，这是因为如果2个堆大小相同，说明当前是偶数个数，下一个元素可能
大于右堆顶，那么插入到左边，左边=右边个数+1，此时调整后右边=左边+1，恰好维护。
*/

int main() {
    int t; cin >> t;
    while (t --) {
        int kase, n;
        cin >> kase >> n;

        cout << kase << ' ' << (n + 1) / 2 << endl;

        priority_queue<int> right;
        priority_queue<int, vector<int>, greater<int> > left;

        int cnt = 0; //输出计数器 10个就换行

        for (int i = 1; i <= n; i++) {
            int x; cin >> x;
            if (right.empty() || x < right.top()) right.push(x);
            else left.push(x);

            if (right.size() > left.size() + 1) left.push(right.top()), right.pop();
            if (left.size() > right.size()) right.push(left.top()), left.pop();

            if (i & 1) {
                cout << right.top() << ' ';
                if (++cnt % 10 == 0) puts("");
            }
        }
        if (cnt % 10) puts(""); //末尾不足10个，就要输出回车，如果已经10个，上边已经输出就不用了
    }
    return 0;
}