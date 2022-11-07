/*例题:字串变换
已知有两个字串 A, B 及一组字串变换的规则（至多6个规则）:
A1 -> B1
A2 -> B2
…
规则的含义为：在 A 中的子串 A1 可以变换为 B1、A2 可以变换为 B2 …。例如：A＝’abcd’ B＝’xyz’
变换规则为：
‘abc’->‘xu’ ‘ud’->‘y’ ‘y’->‘yz’
则此时，A 可以经过一系列的变换变为 B，其变换的过程为：
‘abcd’->‘xud’->‘xy’->‘xyz’
共进行了三次变换，使得 A 变换为B若在 10 步（包含 10步）以内能将 A 变换为 B ，则输出最少的变换步数；否则输出”NO ANSWER!”
输入格式如下：
A B
A1 B1
A2 B2 |-> 变换规则
… … /
所有字符串长度的上限为 20。
*/
//双向BFS一般都是在最少步数模型的题中，floodfill和最短路不用
//双向BFS的过程中，每次选择规模较小的一端进行扩展，来平衡
const int N = 6;
string a[N], b[N];
int n; //规则的数量
int extend(queue<string> &q, unordered_map<string, int> &da, unordered_map<string, int> &db, string a[], string b[]) {
    string t = q.front();
    q.pop();
    for (int i = 0; i < t.size(); i++) // 逐个位置字符
        for (int j = 0; j < n; j++) //枚举规则
            if (t.substr(i, a[j].size()) == a[j]) { //匹配规则a
                string state = t.substr(0, i) + b[j] + t.substr(i + a[j].size()); //替换匹配上的中间一段，然后拼接起来为新的字符串
                if (db.count(state)) return da[t] + 1 + db[state]; //a可以扩展到t，t也可以扩展到state，b也可以扩展到state 那么ab连通
                if (da.count(state)) continue ; //只有第一次扩展才需要加进来
                da[state] = da[t] + 1;
                q.push(state);
            }
    return 11;  //没有和另外一端连通
}
int bfs(string A, string B) { //起点和终点
    queue<string> qa, qb;
    unordered_map<string , int> da, db; //两边到中点的距
    qa.push(A), da[A] = 0;  //起点开始搜
    qb.push(B), db[B] = 0; //终点开始搜
    while (qa.size() && qb.size()) { //一旦某一端没有元素了 说明ab没有连通
        //从较小的一端开始扩展 把a变成b 或者b变成a
        int t; //判断相遇需要的步数
        if (qa.size() <= qb.size()) t = extend(qa, da, db, a, b);
        else t =  extend(qb, db, da, b, a);
        if (t <= 10) return t;
    }
    return 11;
}
int main() {
    string A, B;
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) n++; //规则的数量不一定，所以要统计
    int step = bfs(A, B);
    if (step > 10) puts("NO ANSWER!");
    else cout << step << endl;
    return 0;
}