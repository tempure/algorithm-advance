# 推公式，题意就是求恰好有2个质因子的数个数
# 思路就是逆向从质因子来考虑，每个素数乘上比自己大的素数，在一定范围内，然后求和即可
# 每个素数都乘大与等于自己的素数，是为了保证不重复计数, 同时注意题目范围严格大于 1e8
# https://pe.metaquant.org/pe187.html
# ans = 17427258
# 用 sympy 库内置的求素数个数函数 pi 以及求某个范围内的素数

from sympy import primerange,primepi

def main(N=10**8):
    c =  0
    u = int(N**0.5)
    primes = primerange(u+1)
    for i,p in enumerate(primes):
        c += primepi((N-1)//p)-i
    return c

if __name__ == '__main__':
    print(main())