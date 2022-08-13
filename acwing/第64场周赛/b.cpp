#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        string st;
        cin >> st;
        if (st[st.size() - 1] == 'o' && st[st.size() - 2] == 'p')puts("FILIPINO");
        else if (st[st.size() - 1] == 'u' && st[st.size() - 2] == 's' && st[st.size() - 3] == 'e' && st[st.size() - 4] == 'd' || st[st.size() - 1] == 'u' && st[st.size() - 2] == 's' && st[st.size() - 3] == 'a' && st[st.size() - 4] == 'm')puts("JAPANESE");
        else puts("KOREAN");
    }
}