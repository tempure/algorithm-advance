import numpy as np
from sympy import isprime
import time

"""
Apple M2 上只需17s即可算出答案

思路当然就是暴力了，这题的瓶颈在筛法上，因为数据范围是 1e8 的，一般线性筛搞不定
问题是我也不会杜教筛这类算法。。。不知道快慢相比代码里面用的如何。
筛完之后就每个素数减去1，然后暴力判断是否符合条件就行了。。。

https://pe.metaquant.org/pe357.html

SO 上筛出(1~N)内的素数算法讨论：https://stackoverflow.com/q/2068372/13927708

ans =  1739023853137
time cost:  17.586708068847656
"""

st = time.time()

def prime_sieve(n):
    sieve = np.ones(n//3+(n%6==2), dtype=bool)
    sieve[0] = False
    for i in range(int(n**0.5)//3+1):
        if sieve[i]:
            k=3*i+1|1
            sieve[((k*k)//3)::2*k] = False
            sieve[(k*k+4*k-2*k*(i&1))//3::2*k] = False
    return np.r_[2,3,((3*np.nonzero(sieve)[0]+1)|1)]

def is_valid(n):
    u = int(n**0.5) + 1
    for i in range(2,u):
        if n % i == 0:
            if not isprime(i+n//i):
                return False
    return True 

def main(N=10**8):
    arr = prime_sieve(N) - 1
    print("ans = ", arr[np.vectorize(is_valid)(arr)].sum())

if __name__ == '__main__':
    main()

end = time.time()
print("time cost: ", end -st)



