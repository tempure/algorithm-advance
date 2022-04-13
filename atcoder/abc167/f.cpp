#include<bits/stdc++.h>
using namespace std;

//https://zhuanlan.zhihu.com/p/139779679
//就是贪心，左括号比右括号多的序列全部放前面，后面是反过来对称

//按照这个题解的代码实现，放前面一半的，注意r不一定是0，比如 ()))))((((( 这个字符串 l = 5, r = 4
//同理放后面的，l也不一定是0, 所以还是需要排序的，，，

//放最左边的串肯定  r = 0

//左边不能按照l降序贪心排序，只能按照r升序，))(((( 这种样例按照l降序就不行，，

struct node {
    int l, r;
};
const int N = 1e6 + 7;
string s[N];
int n;

vector<node>a;
vector<node>b;

bool cmp(node x, node y) {
    return x.r < y.r;
}

bool cmp1(node x, node y) {
    return x.l < y.l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout .tie(0);
    //scanf("%d", &n);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        int len = s[i].length();
        int l = 0, r = 0;
        for (int j = 0; j < len; j++) {
            if (s[i][j] == '(') l++;
            else if (l) l--;
            else r++;
        }
        if (l >= r) a.push_back({l, r});
        else b.push_back({l, r});
    }
    sort(a.begin(), a.end(), cmp);
    sort(b.begin(), b.end(), cmp1);
    // for (auto t : a) {
    //     cout << t.l << ' ' << t.r << endl;
    // }
    // cout << "----------" << endl;
    // for (auto t : b) {
    //     cout << t.l << ' ' << t.r << endl;
    // }
    int sum = 0, ok = 0;
    for (int i = 0; i < a.size(); i++) {
        sum -= a[i].r;
        if (sum < 0) {
            ok = 1;
            break;
        }
        sum += a[i].l;
    }
    int sum1 = 0;
    for (int i = 0; i < b.size(); i++) {
        sum1 -= b[i].l;
        if (sum1 < 0) {
            ok = 1;
            break;
        }
        sum1 += b[i].r;
    }
    if (ok) {
        puts("No");
    } else {
        if (sum == sum1) {
            puts("Yes");
        } else {
            puts("No");
        }
    }

}