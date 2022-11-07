/*
满足如下条件的序列X（序列中元素被标号为1、2、3…m）被称为“加成序列”：
1、X[1]=1
2、X[m]=n
3、X[1]<X[2]<…<X[m-1]<X[m]
4、对于每个 k（2≤k≤m）都存在两个整数 i 和 j （1≤i,j≤k−1，i 和 j 可相等），使得X[k]=X[i]+X[j]。
给定一个整数n，找出符合上述条件的长度m最小的“加成序列”。
如果有多个满足要求的答案，只需要找出任意一个可行解。
输入包含多组测试用例。每组测试用例占据一行，包含一个整数n。当输入为单行的0时，表示输入结束。
输出格式
对于每个测试用例，输出一个满足需求的整数序列，数字之间用空格隔开。每个输出占一行。
输入样例：
5
7
12
15
77
0
输出样例：
1 2 4 5
1 2 4 6 7
1 2 4 8 12
1 2 4 5 10 15
1 2 4 8 9 17 34 68 77
*/
const int N = 110;
int path[N];
int n;
//从大到小枚举下一个数 可以减少长度
//排除冗余：如果已经有2个数等于某个数 就不用尝试其它的数
bool dfs(int u, int max_depth) { //当前层数 最大层数
    if (u > max_depth)return false;
    //u-1是因为必须搜索完上一层，这一层开始才能判断是否符合
    if (path[u - 1] == n) return true;
    //将st数组开在dfs里面，原因: 因为path是全局，每次dfs更新的都是当前位置
    //的元素，双重循环只需要判重在此之前的元素的组合之后的和
    //所以每次都会初始化st数组 重新判定
    bool st[N] = {0};
    for (int i = u - 1; i >= 0; i--) //枚举2个数的和
        for (int j = i; j >= 0; j--) {
            int s = path[i] + path[j];
            // s <= path[u-1]  因为要保持序列的严格递增
            if (s > n || s <= path[u - 1] || st[s]) continue;
            st[s] = true;
            path[u] = s;
            if (dfs(u + 1, max_depth)) return true;
        }
    return false;
}
int main() {
    while (~scanf("%d", &n) && n) {
        path[0] = 1;
        int depth = 1;
        while (!dfs(1, depth)) depth++;
        for (int i = 0; i < depth; i++) cout << path[i] << ' ';
        cout << endl;
    }
    return 0;
}