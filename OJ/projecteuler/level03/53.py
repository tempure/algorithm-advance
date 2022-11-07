# https://pe.metaquant.org/pe053.html
# 根据对称性优化
# ans = 4075

from math import factorial as fac

def comb_num(n,k):
    num = fac(n)/(fac(n-k)*fac(k))
    return num

def main():
    count = 0
    for n in range(23,101):
        for r in range(1,n//2):
            if comb_num(n,r) > 10**6:
                count += (n - 2*r + 1)
                break
    return count

if __name__ == '__main__':
    print(main())