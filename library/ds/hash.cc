/*
维护一个集合，支持如下几种操作：
I x，插入一个数 x；
Q x，询问数 x 是否在集合中出现过；
现在要进行 N 次操作，对于每个询问操作输出对应的结果。
输入格式:第一行包含整数 N，表示操作数量。
接下来 N 行，每行包含一个操作指令，操作指令为 I x，Q x 中的一种。
输出格式:对于每个询问指令 Q x，输出一个询问结果，如果 x 在集合中出现过，则输出 Yes，否则输出 No。每个结果占一行。
数据范围:1<=N<=1e5, −1e9<=x<=1e9
输入样例：
5
I 1
I 2
I 3
Q 2
Q 5
输出样例：
Yes
No
*/
/*
开放寻址法，开一维数组，长度为插入总数的2到3倍(经验值)
比2到3倍大的第一个质数即可，用get_prim()函数得到
*/
const int N = 200003;  //2 ~ 3倍找质数取模
const int null = 0x3f3f3f3f;  //初始化值，该数要超过所有插入的数的范围
int h[N];
int get_prim(int x) { //得到第一个比x大的质数作为N,比赛先求
    for (int i = x;; i++) {
        bool flag = true;
        for (int j = 2; j * j <= i; j++)
            if (i % j == 0) {
                flag = false;
                break;
            }
        if (flag) return i;
    }
}
int find(int x) {//同时实现返回插入的位置以及是否找到的作用
    int k = (x % N + N) % N;
    while (h[k] != null && h[k] != x) { //等于null就直接返回 插入到null这个位置就可以了
        k++;
        if (k == N) k = 0; //到末尾了 那就重新到开头开始找
    }
    return k;//查找的时候，如果没找到，直接返回null
}
int main() {
    int n; cin >> n;
    char s; int x;
    memset(h, 0x3f, sizeof h);
    while (n --) {
        cin >> s;
        if (s == 'I') {
            cin >> x;
            h[find(x)] = x;
        } else {
            cin >> x;
            if (h[find(x)] != null) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return 0;
}

/*开放寻址法中, 如果key不是单一元素，比如key是pair<int,int>, 举例假设同时维护<r,t>, 技巧就是将t直接拼接在r后面作为值进行取模。需要注意的就是t的位数大小，比如t最多为2位数, 那么可以用 r * 100 + t 来取模*/
//例题: https://www.acwing.com/problem/content/4614/

int find(int r, int t) {
    LL key = r * 100ll + t;
    int k = key % M;
    while (h[k] != -1 && h[k] != key)
        if ( ++ k == M)
            k = 0;
    //注意我们可以同时维护更多的值, 比如 cnt[]
    if (h[k] == -1) h[k] = key, cnt[k] = 0;
    return k; //返回哈希结果数组中的下标位置
}

/*
拉链法：本质就是邻接表，每次哈希之后的结果如果有冲突，就直接在该位置的head处直接向下拉链即可
询问是否存在，则同样先求hash之后的head位置，然后在该head的侧链上遍历，模数是大于插入总数的第一个质数
和开放寻址法不一样，不用开2倍。
*/
const int N = 100003; //求得的质数
int e[N], ne[N], h[N], idx;
void insert(int x) {
    int k = (x % N + N) % N;
    e[idx] = x;
    ne[idx] = h[k];
    h[k] = idx ++;
}
bool find(int x) {
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i])//从侧链开始找
        if (e[i] == x) return true;
    return false;
}
int main() {
    int n; cin >> n;
    string s; int x;
    memset(h, -1, sizeof h);
    while (n--) {
        cin >> s;
        if (s == "I") {
            cin >> x;
            insert(x);
        } else {
            cin >> x;
            if (find(x)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return 0;
}
