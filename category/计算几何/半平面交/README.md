### CQOI2006以及 S&I 算法 细节理解：

- q[]队列里面存的是边的编号
- cmp 函数 如果平行，排序会把靠左的边放在较前的位置

```cpp
bool cmp(const Line &a, const Line &b) {
    double A = get_angle(a), B = get_angle(b);
    if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0;
    return A < B;
}
```

### S&I 算法每次都要先更新队尾，后更新队头的解释：

对于假如一个新的边，能把所有边都弹出去的特殊情况，参考oi-wiki的三条边的[特殊情况](https://oi-wiki.org/geometry/half-plane/#_7)

这样如果先更新队头，那么就把第一条加的边删掉了，这样就留下了后加入的两条边

此时 `hh+1=tt`,队中只有两条边，停止更新了

如果先更新队尾，那么就留下了第一条和第三条边，这才是正确的直线平面交集


### 此算法在无解的情况下也能返回面积为0的正确结果，特殊数据构造2个正方形如下：
```
2
4
1 0
2 0
2 1
1 1
4
4 0
5 0
5 1
4 1
```
Debug 代码：
```cpp
cout << "k=" << k << endl;
for(int i =0; i <k; i++){
    cout << intersec[i].x << ' ' << intersec[i].y << endl;
}
```
输出：
```
k=2
-nan inf
-nan inf
0.000
```

### corner case：
对于 n = 1 的情况，也就是只有一个多边形的情况下，也能求出答案，如下三角形
- 前提是必须要逆时针给出所有点，或者顺时针，取决于模板怎么实现
- 但是此题规定了 n >= 2, 所以不存在这种 corner case
```
1
3
1 0
3 0
2 1
```

>对于不相交的2个多边形，答案会计算出0的正确答案，因为按照算法的流程来说，会排除掉所有
靠右的斜率相同的边，考虑2个不相交的正方形：我们永远不能让一个正方形的所有边，在逆时针方向的向量上
让其所有边都位另外一个正方形的左边使其不被队列中排除掉，所以无法构造出交集的多边形。