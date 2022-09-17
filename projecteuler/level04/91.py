# 分类讨论，比暴力更高效
# 注意除以 gcd 得到最小移动坐标的常用技巧
# https://pe.metaquant.org/pe091.html
# ans = 14234

from math import gcd

def main(N=50):
    count = 0
    for x in range(1,N+1):
        for y in range(1,N+1):
            g = gcd(x,y)
            low = max(-g*x/y,(y-N)*g/x)
            up = min(g*(N-x)/y,g*y/x)
            count += (int(up)-int(low))
    return count + 3*50**2

if __name__ == '__main__':
    print(main())