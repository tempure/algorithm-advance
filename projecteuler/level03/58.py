# https://pe.metaquant.org/pe058.html
# 从右下角完全平方数入手递推
# ans = 26241

from itertools import count
from sympy import isprime

def main():
    k = 0
    for i in count(3,2):
        a = i**2 - (i-1) # i 为边长
        b = a - (i-1)
        c = b - (i-1)
        k += len([x for x in [a,b,c] if isprime(x)])
        n = 2 * i - 1
        if k/n < 0.1:
            return i

if __name__ == '__main__':
    print(main())