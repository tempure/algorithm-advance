#include <bits/stdc++.h>
using namespace std;
string s, s1, s2;
int a, b, p, t;
int main()
{
    ios::sync_with_stdio(false);
    cin >> s;
    t = 0;
    s1 = "";
    int len = s.length();
    cout << "f'(x)=";
    p = 5;
    for (int i = 5; i < len; i = ++p)
    {
        if (s[i] == 'x')
        {
            int len1 = s1.length();
            if (s1[len1 - 1] == '-') s1 = "-1";
            if (s1[len1 - 1] == '+') s1 = "1";
            if (s1 == "" || s1 == "+") s1 = "1";
            if (s1 == "-") s1 = "-1";
            stringstream ss;
            ss << s1;
            ss >> a;
            s1 = "";
            if (s[i + 1] == '^')
            {

                for (int k = i + 2; k < len && s[k] != '-' && s[k] != '+'; k++)
                {
                    s2 += s[k];
                    p = k;
                }
                stringstream sss;
                sss << s2;
                sss >> b;
                if (b > 2)
                {
                    cout << ((a > 0 && t) ? "+" : "") << a*b << "x" << "^" << b - 1;
                }
                else
                {
                    cout << ((a > 0 && t) ? "+" : "") << a*b << "x";
                }

            }
            else
            {
                cout << ((a > 0 && t) ? "+" : "") << a;
            }
            s2 = "";
            t++;
        }
        else
        {
            s1 += s[i];
        }
        if (!t && (s[i] == '-' || s[i] == '+'))
        {
            s1 = s[i];
        }
    }
    if (!t) cout << "0";
    return 0;
}
