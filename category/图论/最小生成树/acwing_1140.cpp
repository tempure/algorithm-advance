#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 110;
int g[N][N], d[N];
bool v[N];
int n;

void prim(){
    d[1] =0;
    for(int i = 1; i <= n - 1; i++){
        int x = 0;
        for(int j = 1; j <= n; j++)
            if(!v[j] && (x == 0 || d[j] < d[x])) x = j;
        v[x] = 1;
        
        for(int y = 1; y <= n; y++)
            if(!v[y]) d[y] = min(d[y], g[x][y]);
    }
}

int main(){
    memset(v, 0, sizeof v);
    memset(d, 0x3f, sizeof d);
    memset(g, 0x3f, sizeof g);
    
    cin >> n;

    for(int i = 1; i<= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> g[i][j];
            

    prim();
    
    int  res = 0;
    for(int i = 2; i <=n ; i++) res += d[i];
    cout << res << endl;
    return 0;
}