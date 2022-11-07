/*
1插入数值x
2删除数值x(若有多个相同的数，应只删除一个)。
3查询数值x的排名(若有多个相同的数，应输出最小的排名)。
4查询排名为x的数值。
5求数值x的前驱(前驱定义为小于x的最大的数)。
6求数值x的后继(后继定义为大于x的最小的数)。
注意： 数据保证查询的结果一定存在。
*/
const int N = 100010;
const int INF = 1e8; //边界点
struct Node {
    int l, r;
    int key, val;
    int cnt, sz; //该数出现的次数 每个以当前根的子树的大小
} tr[N];
int n; //题目操作数
int root, idx;
void pushup(int p) {
    tr[p].sz = tr[tr[p].l].sz + tr[tr[p].r].sz + tr[p].cnt;
}
int get_node(int key) { //创建节点
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = 1;
    tr[idx].sz = 1;
    return idx;
}
void build() {
    get_node(-INF), get_node(INF);
    root = 1, tr[1].r = 2;
    pushup(root);
}
void zig(int &p) { //右旋转 注意传入的是引用
    int q = tr[p].l;
    tr[p].l = tr[q].r;
    tr[q].r = p;
    p = q; //更改指针的指向
    //刷新改变的位置以及在原树中的节点的位置
    pushup(tr[p].r), pushup(p);
}
void zag(int &p) {
    int q = tr[p].r;
    tr[p].r = tr[q].l;
    tr[q].l = p;
    p = q;
    pushup(tr[p].l), pushup(p);
}
void insert(int &p, int key) {
    if (!p) p = get_node(key);
    else if (tr[p].key == key) tr[p].cnt ++;
    else if (tr[p].key > key) {
        insert(tr[p].l, key);
        if (tr[tr[p].l].val > tr[p].val) zig(p); //不满足堆的性质 就右旋
    }
    else {
        insert(tr[p].r, key);
        if (tr[tr[p].r].val > tr[p].val) zag(p); //左旋
    }
    pushup(p);
}
void del(int &p, int key) {
    if (!p) return ;
    if (tr[p].key == key) {
        if (tr[p].cnt > 1) tr[p].cnt --;
        else if (tr[p].l || tr[p].r) { //不是叶节点
            // 如果右子树是空 或者左子树val大于右子树 那么就向下右旋
            if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) {
                zig(p);
                //p在树上是个固定位置的指针
                //zig之后原来的p会跑到右边子节点 但是新的p依然固定的位置
                del(tr[p].r, key);
            } else {
                zag(p);
                del(tr[p].l, key);
            }
        }
        else p = 0; //是子节点1
    }
    else if (tr[p].key > key) del(tr[p].l, key);
    else  del(tr[p].r, key);
    pushup(p);
}
int get_rank_by_key(int p, int key) { //通过数值找排名
    if (!p) return 0; //无解的情况
    if (tr[p].key == key) return tr[tr[p].l].sz + 1;
    //要查找的key比当前节点的key小 那么就去左树查排名
    if (tr[p].key > key) return get_rank_by_key(tr[p].l, key);
    //去右子树查在右子树的排名 所以要加上左子树的size
    return tr[tr[p].l].sz + tr[p].cnt + get_rank_by_key(tr[p].r, key);
}
int get_key_by_rank(int p, int rank) { //通过排名找数值
    if (!p) return INF; //本题不会发生 比如只有99点 问第1000个点的排名
    //当前节点子树比 rank还大 那就去左子树找
    if (tr[tr[p].l].sz >= rank) return get_key_by_rank(tr[p].l, rank);
    //左边的太小 但是加上现在节点cnt又太大 那么当前节点的key必然就是答案
    if (tr[tr[p].l].sz + tr[p].cnt >= rank) return tr[p].key;
    //在右子树的排名要先减掉左子树和当前节点的cnt
    return get_key_by_rank(tr[p].r, rank - tr[tr[p].l].sz  - tr[p].cnt);
}
//找到严格小于key的最大数
//注：找到小于等于key的最小数 板子里面的符号改成大于就行了
int get_prev(int p, int key) {
    if (!p) return -INF;
    if (tr[p].key >= key) return get_prev(tr[p].l, key);
    //如果比当前节点的key大 那么当前的key可能是答案 去右子树找的时候取max即可
    return max(tr[p].key, get_prev(tr[p].r, key));
}
//找到大于key的最小数
//找到大于等于key的最小数 板子里面的符号改成小于就行了
int get_next(int p, int key) {
    if (!p) return INF;
    if (tr[p].key <= key) return get_next(tr[p].r, key);
    return min(tr[p].key, get_next(tr[p].l, key));
}
int main() {
    build();
    scanf("%d", &n);
    while (n --) {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1) insert(root, x);
        else if (opt == 2) del(root, x);
        //由于build时候加入了-INF节点 查rank和key时候 注意加一减一
        else if (opt == 3) printf("%d\n", get_rank_by_key(root, x) - 1);
        else if (opt == 4) printf("%d\n", get_key_by_rank(root, x + 1));
        else if (opt == 5) printf("%d\n", get_prev(root, x));
        else if (opt == 6) printf("%d\n", get_next(root, x));
    }
    return 0;
}