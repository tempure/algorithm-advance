# ans = 71
# https://pe.metaquant.org/pe077.html
# dp[i][j] 表示用前j个素数表示i的方法数
# 代码对数组下标从1开始, 和状态转移方程一致
# 为什么初始化状态 dp[0][j] = 1 ??

from sympy import primepi
from functools import lru_cache

primes = ["", 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79]

@lru_cache(maxsize=2048)
def ways(x,y):
    if x == 0:
        return 1
    elif x == 1:
        return 0
    elif y == 1:
        return 0 if x%2==1 else 1
    elif x < primes[y]:
        return ways(x,y-1)
    else:
        return ways(x,y-1) + ways(x-primes[y],y)

def main(N=5000):
    i = 11
    while True:
        w = ways(i,primepi(i))
        if w > N:
            return i
        else:
            i += 1

if __name__ == '__main__':
    print(main())