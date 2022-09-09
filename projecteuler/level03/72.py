# https://pe.metaquant.org/pe072.html
# 欧拉函数前缀和 数论分块做法
# ans = 303963552391

from functools import lru_cache

def number_theory_block(f,n,i=1):
    ans = 0
    while i <= n:
        j = n//(n//i)
        ans += (j-i+1)*f(n//i)
        i = j + 1
    return ans

@lru_cache(maxsize=2048)
def sum_of_euler_phi(n):
    if n == 1:
        return 1
    else:
        return n*(n+1)//2 - number_theory_block(sum_of_euler_phi,n,2)

def main(N=10**6):
    return sum_of_euler_phi(N)-1

if __name__ == '__main__':
    print(main())