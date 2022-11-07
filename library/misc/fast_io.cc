template <typename T>
inline T
read() { //支持负数 不支持浮点数
    T sum = 0, fl = 1;
    int ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') fl = -1;
    for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
    return sum * fl;
}
// int a = read<int>();
// long long b = read<long long>();
// __int128 c = read<__int128>();
template <typename T>
void print(T x) {
    if (x < 0) {  //支持负数 不支持浮点数
        x = -x;
        putchar('-');
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
//__int128 x = __int128(1) << 100;
//print(-x);