#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//提前break题意：如果前i个已经推出所有关系 即使第i + 1 个矛盾 也当作成立
//矛盾判断：d[i][i] == 1 因为A > B, B > A ->  A > A 
//唯一确定：d[i][j], d[j][i] 必有一个是1 一个是0
//不能确定：d[i][j] == 0 && d[j][i] == 0
//排序：一个没有被其他数标记过的数 就是最小数

const int N = 26;
int n,m ;
bool g[N][N], d[N][N];
bool st[N];

void floyd(){
    memcpy(d, g, sizeof d);
    
    for(int k = 0; k < n; k++)
        for(int i = 0; i <n; i++)
            for(int j = 0; j < n; j++)
            d[i][j] |= d[i][k] && d[k][j];
}

int check(){
    for(int i = 0; i <n; i++)
        if(d[i][i]) return 2;
        
    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++) //注意这里是枚举点对 i,j 所以j不是1到n 不然会重复
            if(!d[i][j] && !d[j][i]) //都是0  也就是不能确定
                return 0;
    
    return 1; //唯一确定
}

char get_min(){
    for(int i = 0; i < n; i++)
        if(!st[i]){
            bool flag = true;
            for(int j = 0; j < n; j++) //找找有没有比i小的 并且没有标记的 这里找到的一定是最下的 因为i是从0开始枚举的
                if(!st[j] && d[j][i]){
                    flag = false;
                    break;
                }
            if(flag){
                st[i] = true; 
                return 'A' + i;
            }
        }
}

int main(){
    while(cin >> n >> m , n || m){
        memset(g, 0, sizeof g);
        int type = 0, t;  //type 0不能确定 1唯一确定 2 矛盾 t 轮数
        
        for(int i = 1; i <= m; i++){ //迭代m次 就是m个不等式关系
            char str[5];
            cin >> str;
            int a = str[0] - 'A', b = str[2] - 'A'; 
            
            if(!type){ //只有当所有状态都确定了 就不会进入这个判断了
            //floyd 每加一个大小关系就i判断一下 目的就是最早break 题意
                g[a][b] = 1;
                floyd();
                type = check();
                if(type) t= i;
            }
        }
        
        if(!type) puts("Sorted sequence cannot be determined.");
        else if(type == 2) printf("Inconsistency found after %d relations.\n", t);
        else { //唯一确定
            memset(st, 0, sizeof st);
            printf("Sorted sequence determined after %d relations: ", t);
            
            for(int i = 0; i <n; i++) printf("%c", get_min());
            printf(".\n");
        }
    }        
    return 0;
}