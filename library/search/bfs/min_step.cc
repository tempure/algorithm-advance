/* 例题
1 2 3 4  //基本状态
8 7 6 5
A：交换上下两行；
B：将最右边的一列插入到最左边；
C：魔板中央对的4个数作顺时针旋转。
输入仅一行，包括 8 个整数，用空格分开，表示目标状态。
输出文件的第一行包括一个整数，表示最短操作序列的长度。
如果操作序列的长度大于0，则在第二行输出字典序最小的操作序列。
*/
//最小步数模型的BFS里面，序列的状态使用哈希来存 包括八数码模型
//此题就用stl的unordered_map即可
//转移路径 就和迷宫那道题一样 记录一下转移的pre数组即可
//字典序的处理:每次都按照A B C的转移方式依次搜索
char g[2][4];
unordered_map<string, int> dist; //状态的步数
//从哪个状态转移过来的，操作用char存储
unordered_map<string, pair<char, string> > pre;
queue<string> q;
void set(string state) { //将字符串 顺时针放到矩阵中
    for (int i = 0; i < 4; i++) g[0][i] = state[i];
    for (int i = 3, j = 4; i >= 0; i--, j++) g[1][i] = state[j];
}
string get() { //以顺时针方向取出字符串
    string res;
    for (int i = 0 ; i < 4; i++) res += g[0][i];
    for (int i = 3;  i >= 0; i--) res += g[1][i];
    return res;
}
string move0(string state) {
    set(state);
    for (int i = 0 ; i < 4; i++) swap(g[0][i], g[1][i]);
    return get();
}
string move1(string state) {
    set(state);
    //将最后一列存下来，然后前面的往后移动一位，然后再把最后一列插到第一列
    char v0 = g[0][3], v1 = g[1][3]; //存下最后一列
    for (int i = 3; i > 0; i--)
        for (int j = 0; j < 2; j++)
            g[j][i] = g[j][i - 1];
    g[0][0] = v0, g[1][0] = v1;  //最后一列插到第一列
    return get();
}
string move2(string state) {
    set(state);
    //每一个都顺时针移动，覆盖 存下左上角的元素
    char t = g[0][1];
    g[0][1] = g[1][1];
    g[1][1] = g[1][2];
    g[1][2] = g[0][2];
    g[0][2] = t;
    return get();
}
void bfs(string start, string end) {
    if (start == end) return ; //特判一下不需要操作的样例
    q.push(start);
    dist[start] = 0;
    while (q.size()) {
        auto t = q.front();
        q.pop();
        string m[3];  //三种操作 操作之后可以得到的状态序列 存到m中
        m[0] = move0(t);
        m[1] = move1(t);
        m[2] = move2(t);
        for (int i = 0; i < 3; i++) { //三种操作 遍历
            string str = m[i];
            if (dist.count(str) == 0) {
                dist[str] = dist[t] + 1;
                //是由t状态转移过来的
                pre[str] = {char(i + 'A'), t};
                if (str == end) break;
                q.push(str);
            }
        }
    }
}
int main() {
    int x;
    string start, end; //start是12345678 逆序搜索
    for (int i = 0 ; i < 8; i++) {
        cin >> x;
        end += char(x + '0'); //将数字转为char拼接
    }
    for (int i = 0 ; i < 8; i++) start += char(i + '1');
    bfs(start, end);
    cout << dist[end] << endl;
    string res;
    while (end != start) {
        res += pre[end].first;
        end = pre[end].second;
    }
    //由于是反向搜索的操作顺序，所以需要逆序一下输出
    reverse(res.begin(), res.end());
    if (res.size()) cout << res << endl;
    return 0;
}
