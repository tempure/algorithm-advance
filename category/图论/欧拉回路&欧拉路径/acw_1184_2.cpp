#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 4e5 + 10;
int h[N], e[M], ne[M], idx;
bool used[M];
int ans[M], cnt; //ans记录欧拉回路的边
int din[N], dout[N];

int type, n, m;

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u){
    while(h[u] != -1){
        int i = h[u];
        if(used[i]){
            h[u] = ne[i];
            continue;
        }
        h[u] = ne[i];
        used[i] = true;
        if(type == 1) used[i ^ 1] = true;
        dfs(e[i]);
        if(type == 1){
            int t = i / 2 + 1; //边编号从1开始，但是加边idx从0开始，注意
            if(i & 1) t *= -1;
            ans[++cnt] = t;
        } 
        else ans[++cnt] = i + 1;
    }
}

void solve(){
    cin >> type;
    cin >> n >> m;
    memset(h, -1, sizeof h);

    for(int i= 0; i< m; i++){
        int a,b;
        cin >> a >> b;
        add(a,b);
        if(type == 1) add(b,a);
        din[b]++, dout[a]++;
    }

    //先判断无解的情况，然后再dfs求方案
    if(type == 1){
        for(int i= 1; i<= n; i++)
            if(din[i] + dout[i] & 1){ //总度数不是偶数
                cout << "NO" << endl;
                return;
            }
    }
    else{
        for(int i =1; i <= n; i++)
            if(din[i] != dout[i]){
                cout << "NO" << endl;
                return;
            }
    }

    for(int i =1; i<= n; i++)
        if(h[i] != -1){
            dfs(i);
            break;
        }
    if(cnt < m){
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    for(int i = cnt; i ;i --) cout << ans[i] << ' ';
    cout << endl;
}

int main(){
    solve();
    return 0;
}