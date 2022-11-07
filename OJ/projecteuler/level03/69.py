# https://pe.metaquant.org/pe069.html
# 推公式 只需要使得求出对于 n <= 1e6 中质因数最多的数即可
# ans = 510510

from sympy import prime

def main(N=10**6):
    i,prod,arr = 1,1,[]
    while prod <= N:
        prod *= prime(i)
        arr.append(prod)
        i += 1
    return arr[-2]


if __name__ == '__main__':
    print(main())