#include <bits/stdc++.h>
using namespace std;

/*
有向图判断是否存在欧拉路径，欧拉回路也是欧拉路径的一种,本题中存在欧拉回路就是最后一个字单词结尾和开头单词第一个字母相同的情况
另外还要判断是否存在孤立的两个字母组成的边，用DSU维护，如果存在说明无解
*/

const int N = 30;
int n, m;
int p[N];
bool st[N];
int din[N], dout[N];

int find(int x){
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void solve(){
    char str[1010];
    cin >> n;
    memset(din, 0, sizeof din);
    memset(dout, 0, sizeof dout);
    memset(st, 0, sizeof st);

    for(int i = 0; i< 26; i++) p[i] = i;
    for(int i = 0; i < n; i++){
        cin >> str;
        int len = strlen(str);
        int a= str[0] - 'a', b = str[len-1] - 'a';
        st[a] = st[b] = true;
        dout[a] ++, din[b]++;
        p[find(a)] = find(b);
    }
    int start = 0, end = 0;
    bool flag = true;
    for(int i=  0; i < 26; i++)
        if(din[i] != dout[i]){
            if(din[i] == dout[i] + 1) end++;
            else if(dout[i] == din[i] + 1) start++;
            else{
                flag = false;
                break;
            }
        }
    if(flag && !(!start && !end || start == 1 && end == 1)) flag = false;

    int rep = -1;
    for(int i =0; i< 26; i++)
        if(st[i]){
            if(rep== -1) rep = find(i);
            else if(rep != find(i)){
                flag = false;
                break;
            }
        }
    if (flag) puts("Ordering is possible.");
    else puts("The door cannot be opened.");
}

int main(){
    int t = 1;
    cin >> t;
    while(t --) solve();
    return 0;
}