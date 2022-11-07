# 解法同 108 题
# https://pe.metaquant.org/pe110.html
# ans = 9350130049860600

from sympy import factorint
from functools import reduce
from operator import mul,add

def prime_product(factors):
    primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
    powers = sorted(reduce(add,[[(k-1)//2]*v for k,v in factors.items()]),reverse=True)
    bases = primes[:len(powers)]
    res = reduce(mul,[b**p for b,p in zip(bases,powers)])
    return res

def main(N=int(4e6)):
    n = 2*N - 1
    primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
    while True:
        factors = factorint(n)
        if all(x in [3,5,7] for x in factors.keys()):
            return prime_product(factors)
        n += 2


if __name__ == '__main__':
    print(main())