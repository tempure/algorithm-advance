# 就是和第120题一样的推公式题，而且是个更简单的版本
# https://pe.metaquant.org/pe123.html
# ans = 21035

from sympy import nextprime

def main(N=10**10):
    n,p = 7037,71059
    while True:
        np = nextprime(p,2)
        n = n + 2
        r = 2*n*np
        if r > N:
            return n
        else:
            p = np

if __name__ == '__main__':
    print(main())