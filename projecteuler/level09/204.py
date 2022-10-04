# 思路就是动态规划
# 这个状态转移是设计非常精妙的。。。当然我不懂怎么才能设计出这个状态转移方程
# 而且这个转移方程的分类讨论也是非常精妙且有思维难度的。。。。
# 这个题不能直接用筛法做，因为题意是最大的质因子不能超过，而不是是否包含某个质因子的逻辑
# https://pe.metaquant.org/pe204.html
# ans = 2944730

from math import log
from sympy import isprime
from functools import lru_cache

@lru_cache(maxsize=None)
def hn(n,f):
    if n == 1:
        return 1
    elif f == 2:
        return int(log(n,2))+1
    elif n < f:
        return hn(n,n)
    elif not isprime(f):
        return hn(n,f-1)
    else:
        return hn(n,f-1)+hn(n//f,f)

def main(n=10**9,f=100):
    return hn(n,f)


if __name__ == '__main__':
    print(main())