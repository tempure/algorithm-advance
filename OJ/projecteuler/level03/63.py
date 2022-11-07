# https://pe.metaquant.org/pe063.html
# 推公式
# 链接题解公式等于号不严谨，不等式左边应该为 10^(k-1) <= n^k 但是代码是对的
# ans = 49

from math import log10

def main():
    c = 0
    for n in range(1,10):
        c += int(1/(1-log10(n)))
    return c

if __name__ == '__main__':
    print(main())