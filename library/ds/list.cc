//单链表
// head存储链表头，e[]存储节点的值，ne[]存储节点的next指针，
//idx表示当前用到了哪个节点
int head, e[N], ne[N], idx;
void init() { // 初始化
    head = -1;
    idx = 0;
}
// 在链表头插入一个数a
void insert(int a) {
    e[idx] = a, ne[idx] = head, head = idx ++ ;
}
// 将头结点删除，需要保证头结点存在
void remove() {
    head = ne[head];
}
/*
    例题:实现一个单链表，链表初始为空，支持三种操作：
    (1) 向链表头插入一个数；
    (2) 删除第k个插入的数后面的数；
    (3) 在第k个插入的数后插入一个数
    现在要对该链表进行M次操作，进行完所有操作后，从头到尾输出整个链表。
    注意:题目中第k个插入的数并不是指当前链表的第k个数。例如操作过程中一共插入了n个数，
    则按照插入的时间顺序，这n个数依次为：第1个插入的数，第2个插入的数，…第n个插入的数。
    输入格式: 第一行包含整数M，表示操作次数。
    接下来M行，每行包含一个操作命令，操作命令可能为以下几种：
    (1) “H x”，表示向链表头插入一个数x。
    (2) “D k”，表示删除第k个输入的数后面的数（当k为0时，表示删除头结点）
    (3) “I k x”，表示在第k个输入的数后面插入一个数x（此操作中k均大于0）
*/
const int N = 100010;
int head, e[N], ne[N], idx;
//初始化
void init() {
    head = -1;
    idx = 0;
}
//将 x 插到头节点
void add_to_head(int x) {
    e[idx] = x, ne[idx] = head, head = idx++;
}
//将 x 插到下标是 k 的点后边
void add(int k, int x) {
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx++;
}
//将下标是 k 后边的节点删除
void remove(int k) {
    ne[k] = ne[ne[k]];
}
int main() {
    int m; cin >> m;
    init();
    while (m--) {
        int k,  x;  char op; cin >> op;
        if (op == 'H') { cin >> x; add_to_head(x); }
        else if (op == 'D') {
            cin >> k;
            if (!k) head = ne[head];
            remove(k - 1);
        }
        else {cin >> k >> x; add(k - 1, x);}
    }
    for (int i = head; i != -1; i = ne[i]) printf("%d ", e[i]);
    printf("\n");
    return 0;
}


//双链表
// e[]表示节点的值，l[]表示节点的左指针，r[]表示节点的右指针，idx表示当前用到了哪个节点
int e[N], l[N], r[N], idx;
void init() { // 初始化
    //0是左端点，1是右端点
    r[0] = 1, l[1] = 0;
    idx = 2;
}
void insert(int a, int x) { // 在节点a的右边插入一个数x
    e[idx] = x;
    l[idx] = a, r[idx] = r[a];
    l[r[a]] = idx, r[a] = idx ++ ;
}
void remove(int a) { // 删除节点a
    l[r[a]] = l[a];
    r[l[a]] = r[a];
}
/*
实现一个双链表，双链表初始为空，支持5种操作：
(1) 在最左侧插入一个数；
(2) 在最右侧插入一个数；
(3) 将第k个插入的数删除；
(4) 在第k个插入的数左侧插入一个数；
(5) 在第k个插入的数右侧插入一个数
现在要对该链表进行M次操作,进行完所有操作,从左到右输出整个链表
注意:题目中第k个插入的数并不是指当前链表的第k个数。
例如操作过程中一共插入了n个数，则按照插入的时间顺序，这n个数依次为：
第1个插入的数，第2个插入的数，…第n个插入的数。

第一行包含整数M，表示操作次数。
接下来M行，每行包含一个操作命令，操作命令可能为以下几种：
(1) “L x”，表示在链表的最左端插入数x。
(2) “R x”，表示在链表的最右端插入数x。
(3) “D k”，表示将第k个插入的数删除。
(4) “IL k x”，表示在第k个插入的数左侧插入一个数。
(5) “IR k x”，表示在第k个插入的数右侧插入一个数。
*/
const int N = 100010;
int l[N], r[N], e[N], idx;
void init() {
    r[0] = 1, l[1] = 0; //双链表的收尾都是u虚拟节点 方便处理边界
    idx = 2;
}
void insert(int a, int x) {
// 在第k  (a)个插入的节点后面插入 一个值为x的数 对于左边插入可以直接用这个
//比如在k左边插入 就调用insert(l[k], x);
    e[idx] = x;
    l[idx] = a, r[idx] = r[a];
    l[r[a]] = idx, r[a] = idx ++;
}
void remove(int a) {
    l[r[a]] = l[a];
    r[l[a]] = r[a];
}
int main() {
    int n;
    cin >> n;
    init();
    while (n --) {
        string op;
        int k, x;
        cin >> op;
        if (op == "L") {
            cin >> x;
            insert(0, x);
        } else if (op == "R") {
            cin >> x;
            insert(l[1], x);
        } else if (op == "D") {
            cin >> k;
            remove(k + 1); //idx 从2 开始的
        } else if (op == "IL") {
            cin >> k >> x;
            insert(l[k + 1], x);
        } else {
            cin >> k >> x;
            insert(k + 1, x);
        }
    }
    for (int i = r[0]; i != 1; i = r[i]) cout << e[i] << ' ';
    cout << endl;
    return 0;
}



