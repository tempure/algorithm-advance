//数组模拟栈
// tt表示栈顶
int stk[N], tt = 0;
// 向栈顶插入一个数
stk[ ++ tt] = x;
// 从栈顶弹出一个数
tt -- ;
// 栈顶的值
stk[tt];
// 判断栈是否为空
if (tt > 0) {
    /*code*/
}

/*
单调栈：
给定一个长度为N的整数数列，输出每个数左边第一个比它小的数，如果不存在则输出-1。
*/
stack<int> s;
int main() {
    int n; cin >> n;
    while (n --) {
        int x ; cin >> x;
        while (s.size() && s.top() >= x) s.pop();
        if (!s.size()) cout << -1 << ' ';
        else cout << s.top() << ' '; //第一个数左边没有小的 肯定是-1 所以不用考虑边界
        s.push(x);
    }
    return 0;
}
