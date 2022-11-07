//https://codeforces.com/contest/1629/submission/143646086
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

template<typename T> using vc = vector<T>;
template<typename T> using vvc = vc<vc<T>>;

template<typename T> void smax(T& a, T b) { a = max(a, b); }
template<typename T> void smin(T& a, T b) { a = min(a, b); }

#define X first
#define Y second

#define pb push_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

template<typename T> void read(T& x) { cin >> x; }
template<typename T> void read(vc<T>& v) { for (auto& x : v) cin >> x; }
template<typename T, typename... A> void read(T& x, A&... args) { read(x); read(args...); }

string to_string(char c) { string s = ""; s += c; return s; }
string to_string(const char* s) { return (string)s; }
string to_string(string s) { return s; }
template<typename T> string to_string(T x) {
    bool f = true;
    string rez = "";
    for (auto& i : x) {
        if (!f) rez += ' ';
        f = false;
        rez += to_string(i);
    }
    return rez;
}
template<typename T> void write(T x) { cout << to_string(x); }
template<typename T, typename... A> void write(const T& x, const A&... args) { write(x); write(args...); }
void print() { write("\n"); }
template<typename T, typename... A> void print(const T& x, const A&... args) { write(x); if (sizeof...(args)) write(" "); print(args...); }

void solve() {
    int n;
    read(n);
    vc<int> a(n);
    read(a);
    multiset<int> l, r;
    for (int i = 0; i < n; i++) r.insert(a[i]);
    vc<int> rez;
    int brojac = 0;
    for (int i = 0; i < n; i++) {
        l.insert(a[i]);
        r.erase(r.find(a[i]));
        while (l.find(brojac) != l.end()) brojac++;
        if (r.find(brojac) == r.end()) {
            rez.pb(brojac);
            brojac = 0;
            l.clear();
        }
    }
    print(sz(rez));
    print(rez);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    read(tt);
    while (tt--) solve();
    return 0;
}