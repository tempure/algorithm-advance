# 暴力枚举组合
# https://pe.metaquant.org/pe087.html
# ans = 1097343

from itertools import product
from sympy import primerange

def main(N=5*10**7):
    ans = set()
    square_limit = int(N**(1/2))+1
    cube_limit = int(N**(1/3))+1
    fourth_power_limit = int(N**(1/4))+1
    # 笛卡尔积
    s =  product(primerange(1,square_limit),primerange(1,cube_limit),primerange(1,fourth_power_limit))
    for i,j,k in s:
        p = i**2 + j**3 + k**4
        ans.add(p)
    # print(type(s))
    return len({x for x in ans if x<N})


if __name__ == '__main__':
    print(main())
