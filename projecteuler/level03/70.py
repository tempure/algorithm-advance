# 欧拉公式
# φ(n) 和n不可能互相构成重排列
# https://pe.metaquant.org/pe070.html
# ans = 8319823
# 素数范围有待更严谨证明取 sqrt(1e7) 附近区间.....

from sympy import primerange

def main():
    is_permutation = lambda x,y : "".join(sorted(str(x))) == "".join(sorted(str(y)))
    primes = list(primerange(2000,4000))
    dt = {(x*y,(x-1)*(y-1)):((x*y)/((x-1)*(y-1))) for x in primes for y in primes if x*y<10**7}
    for n,phi_n in sorted(dt,key=dt.get):
        if is_permutation(n,phi_n):
            return n

if __name__ == '__main__':
    print(main())