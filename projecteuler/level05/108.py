"""
https://pe.metaquant.org/pe108.html
1. 题解中的“因为Q的质因数分解已经表明原数n的质因数分解中指数...” 然后下面的一一对应的推导感觉不是非常严谨啊..
能把 d(n^2) 和 prod(2ai+1) 对应只能找到合法的 ai 解，但是不一定是唯一的 ai 解吧...
2. 如何证明最小质因数分解应只包含3,5,7三个素数？不包含2是因为必须是奇数可以理解...

代码也不是非常好理解，python的外部科学计算库真的太多了....
ans = 180180
"""
from sympy import factorint
from functools import reduce
from operator import mul,add

def prime_product(factors):
    primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
    powers = sorted(reduce(add,[[(k-1)//2]*v for k,v in factors.items()]),reverse=True)
    bases = primes[:len(powers)]
    res = reduce(mul,[b**p for b,p in zip(bases,powers)])
    return res

def main(N=1000):
    n = 2*N - 1
    primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
    while True:
        factors = factorint(n)
        if all(x in [3,5,7] for x in factors.keys()):
            return prime_product(factors)
        n += 2


if __name__ == '__main__':
    print(main())