#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

//每个字符串看成边 收尾4个字母看成边的端点
//所求的就是(∑w[i] / N) > mid 和上一题完全一致
//然后算出最大值二分即可 最大值是1000 
//(0, 1000]范围内找不到答案只需要判断一下左端点0即可
//因为边权是 w[i] - mid * 1 , mid如果0都没有正环的话 那么 大于0肯定没有了 即是无解


const int N = 700; //最多有26 *  26 个点
const int M = 100010;

int n;
int h[N], e[M], w[M], ne[M], idx;
double dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

bool check(double mid){
    memset(st, 0, sizeof st);
    memset(dist, 0, sizeof dist);
    memset(cnt, 0, sizeof cnt);

    int hh = 0, tt = 0;
    for(int i = 0; i < 676; i++){ // left 和right都是26进制2位数 也就是点的编号 不会超过676
        q[tt++] = i;
        st[i] = true;
    }
    
    int count = 0; //spfa超时优化 判断迭代的次数
    while(hh != tt){
        int t = q[hh++];
        if(hh == N) hh = 0;
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(dist[j] < dist[t] + w[i] - mid){
                dist[j] = dist[t] + w[i] - mid;
                cnt[j] = cnt[t] + 1;
                if(++count > 10 * n) return true; //玄学优化 迭代次数>10 * n就大概率有解
                if(cnt[j] >= N) return true; //注意是点数 也就是边数 >= 点数到时候 就退出
                //这里不是 一定要确切大于 而是找一个上界就可以 因为最后边数会迭代到无穷大
                if(!st[j]){
                    q[tt++] = j;
                    if(tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }

    return false;
}

int main(){
    char str[1010];
    while(scanf("%d", &n) , n){
        memset(h, -1, sizeof h);
        idx = 0;

        for(int i = 0; i < n; i++){
            scanf("%s", str);
                int len = strlen(str);
                if(len >= 2){  //小于2就相当于没有作用
                    int left = (str[0] - 'a') * 26 + str[1] - 'a'; //当成26进制的数 哈希思路 记录开头和结尾
                    int right = (str[len - 2] - 'a') * 26 + str[len-1] - 'a';
                    add(left, right, len);
                }
        }
        if(!check(0)) puts("No solution");  //0都没有解
        else{
            double l = 0, r = 1000;
            while(r - l > 1e-4){
                double mid = (l + r) / 2;
                if(check(mid)) l = mid;
                else r = mid;
            }
            printf("%f\n", r);
        }
    }
    return 0;
}