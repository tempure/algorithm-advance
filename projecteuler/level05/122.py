# Addition-chain exponentiation: https://en.wikipedia.org/wiki/Addition-chain_exponentiation
# NP 完全问题，Donald E. Knuth 在 TAOCP 书里面给了一个递归式求解1000以下指数次幂对应的算法，对本题最大200的的数据范围足够
# https://pe.metaquant.org/pe122.html
# ans = 1582

from sympy import isprime
from functools import lru_cache

def p(n):
    for i in range(1,int(n**0.5)+1):
        if n % i == 0 and isprime(i):
            return i

def sigma(n):
    arr = [23,43,59,77,83,107,149,163,165,179]
    if n in arr:
        return 1
    else:
        return 0

@lru_cache(maxsize=None)
def m(k):
    if k == 1:
        return 0
    elif k == 2:
        return 1
    elif isprime(k):
        return m(k-1)+1-sigma(k)
    else:
        return min(m(k-1)+1,m(p(k))+m(k//p(k)))-sigma(k)

def main(N=200):
    res = [m(k) for k in range(1,N+1)]
    return sum(res)


if __name__ == '__main__':
    print(main())