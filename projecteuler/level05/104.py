# 每次计算取模是为了避免高精度效率计算很低
# 前10位计算需要用到斐波那契通项公式，以及取对数的技巧
# 感觉技巧性还是挺高的....
# https://pe.metaquant.org/pe104.html
# ans = 329468

from math import log10

def fib_top_digits(k): # F_k 第 k 项
    phi = (1+5**0.5)/2
    d = k*log10(phi) - 0.5*log10(5)
    res = int(pow(10,d-int(d)+8))
    return res

def main(N=10**9):
    is_pandigital = lambda n:set(str(n)) == set('123456789')
    a,b,k = 1,1,2
    while True:
        a,b = b,(a+b)%N
        k = k + 1
        if is_pandigital(b) and is_pandigital(fib_top_digits(k)):
            return k


if __name__ == '__main__':
    print(main())