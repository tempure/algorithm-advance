# https://pe.metaquant.org/pe121.html
# 概率题，可以递归求解，也可以使用生成函数，而且时间复杂度要低很多
# 生成函数的话，获胜概率的分母15轮就是固定的16!, 所以只需要计算分子即可
# 最后计算出获胜概率p，那么最高奖金最高为1/p才不会导致庄家亏损
# ans = 2269


import sympy as sp
from math import prod,factorial

# 生成函数做法

def main1(n=15):
    x = sp.var('x')
    expr = prod([(x+i) for i in range(1,n+1)])
    p = sp.Poly(expr)
    res = factorial(n+1)//sum(p.coeffs()[:n//2+1])
    return res

# 递归做法

from fractions import Fraction as f
from functools import lru_cache
from math import factorial

@lru_cache(maxsize=None)
def prob(n,k):
    if k == 0:
        return f(1,n+1)
    elif n == k:
        return f(1,factorial(n+1))
    else:
        return prob(n-1,k)*f(n,n+1)+prob(n-1,k-1)*f(1,n+1)

def main2(n=15):
    p = sum([prob(n,i) for i in range(n//2+1,n)])
    return 1//p


if __name__ == '__main__':
    print(main1())