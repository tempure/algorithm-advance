#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

int n;
unordered_map<string, string> head, tail;

int main()
{
    cin >> n;
    while (n -- )
    {
        string a, b;
        cin >> a >> b;
        if (!tail.count(a)) head[a] = b, tail[b] = a;
        else head[tail[a]] = b, tail[b] = tail[a], tail.erase(a); //erase 意义不大也可以不写
    }

    cout << head.size() << endl;

    for (auto& [a, b] : head)
        cout << a << ' ' << b << endl;

    return 0;
}