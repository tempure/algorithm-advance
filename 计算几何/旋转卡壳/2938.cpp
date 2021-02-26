#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/*
旋转卡壳 枚举所有对踵点距离max
andrew算法O(NlogN) 单调扫描对踵点O(N)
*/

typedef pair<int, int> pii;
const int N = 50010;

int n;
pii q[N];
int stk[N], top;
bool used[N];

pii operator- (pii a , pii b) {
    return {a.x - b.x, a.y - b.y};
}

int operator *(pii a, pii b) {
    return a.x * b.y - a.y * b.x;
}

int area(pii a, pii b, pii c) {
    return (b - a) * (c - a);
}

int get_dist(pii a, pii b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy; //返回距离平方 题目要求
}

//注意这个和凸包的模板下标不一样 栈下标从0开始
void andrew() {
    sort(q, q + n);
    for (int i = 0; i < n; i++) { //下凸壳
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0) {
            // 凸包边界上的点即使被从栈中删掉，也不能删掉used上的标记
            if (area(q[stk[top - 2]], q[stk[top - 1]], q[i]) < 0)
                used[stk[--top]] = false;
            else top --;
        }
        stk[top++] = i; //栈顶下标从0开始
        used[i] = true;
    }

    //将起点再一次入栈
    used[0] = false;
    for (int i = n - 1; i >= 0; i--) { //求上凸壳
        if (used[i]) continue;
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
            top -- ;
        stk[top++] = i;
    }
    top --; //将栈顶后移 栈内删除0号元素 但是stk数组中还是存在0的 只不过top没指向
}

int rotating_calipers() {
    if (top <= 2) return get_dist(q[0], q[n - 1]); //所有点都共线特判
    int res = 0;
    for (int i = 0, j = 2; i < top; i++) { // d=i e=i+1 de段枚举所有的凸包轮廓
        auto d = q[stk[i]], e = q[stk[i + 1]];
        //j先到第一个边对应的最远的点 然后逆时针单调走
        while (area(d, e, q[stk[j]]) < area(d, e, q[stk[j + 1]])) j = (j + 1) % top;
        res = max(res, max(get_dist(d, q[stk[j]]), get_dist(e, q[stk[j]])));
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &q[i].x, &q[i].y);
    andrew();
    printf("%d\n", rotating_calipers());

    return 0;
}