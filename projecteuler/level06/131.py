# 就按照题意直接推公式就行了
# 技巧就是注意 n + p 与 n 都是立方数，后面的推到就比较简单了
# ans = 173

from sympy import isprime

def main(N=576):
    c = 0
    for i in range(1,N+1):
        if isprime(3*i**2+3*i+1):
            c += 1
    return c


if __name__ == '__main__':
    print(main())