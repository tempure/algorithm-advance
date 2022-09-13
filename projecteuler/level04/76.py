# 整数拆分求方案数 DP
# https://pe.metaquant.org/pe076.html
# ans = 190569291
from functools import lru_cache

@lru_cache(maxsize=2048)
def partition(i,j):
    if i == 1 or j == 1:
        return 1
    elif i <= j:
        return partition(i,i-1)+1
    else:
        return partition(i,j-1) + partition(i-j,j)

def main(N=100):
    return partition(N,N-1)

if __name__ == '__main__':
    print(main())