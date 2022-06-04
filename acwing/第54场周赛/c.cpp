#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1000010;

int n;
char s[N];

//就直接扫一遍就行
//只能修改一个括号，卡到那个右括号比左括号多的点，然后前面所有的右括号都可以修改为左括号都是合法的
//前面合法了再扫一次后面看看是否合法,要都合法才算合法的一次修改

//对于右括号修改为左括号的，直接把字符串镜像一下，然后按照左括号改右括号的跑一次就行了

int work() {
    int cnt = 0, r = 0;
    for (int i = 0; i < n; i ++ )
        if (s[i] == '(') cnt ++ ;
        else {
            cnt -- ;
            r ++ ;
            if (cnt < 0) {
                cnt += 2;
                for (int j = i + 1; j < n; j ++ )
                    if (s[j] == '(') cnt ++ ;
                    else {
                        cnt -- ;
                        if (cnt < 0) return 0;
                    }
                return r;
            }
        }

    return 0;
}

int main() {
    scanf("%d%s", &n, s);

    int l = 0, r = 0;
    for (int i = 0; i < n; i ++ )
        if (s[i] == '(') l ++ ;
        else r ++ ;

    if (r == l + 2) printf("%d\n", work());
    else if (l == r + 2) {
        reverse(s, s + n);
        for (int i = 0; i < n; i ++ )
            if (s[i] == '(') s[i] = ')';
            else s[i] = '(';

        printf("%d\n", work());
    }
    else puts("0");

    return 0;
}