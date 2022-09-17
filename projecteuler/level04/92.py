# 感觉数学严格证明不是很简单啊。。。但是复杂度低
# 数学方法求所有欢乐数的个数，思路就是动态规划，但是复杂度不好分析
# 复杂度主要取决于 get_next() 递降的速度，计算 f(n,k)是O(k)的，n,k 很小近似常数复杂度
# get_next() 的复杂度根据 leetcode 官方题解是 O(log n) 的
# https://pe.metaquant.org/pe092.html
# ans = 8581146
# leetcode 对应题目：https://leetcode.cn/problems/happy-number/
# lc的题只是判断，但是pe是求数量就难多了

from functools import lru_cache
from math import log10

def is_happy(n):
    cycle_members = {4, 16, 37, 58, 89, 145, 42, 20}

    def get_next(number):
        total_sum = 0
        while number > 0:
            number, digit = divmod(number, 10)
            total_sum += digit ** 2
        return total_sum

    while n != 1 and n not in cycle_members:
        n = get_next(n)

    return n == 1

@lru_cache(maxsize=None)
def f(n,k):
    if n == k == 0:
        return 1
    elif n < 0:
        return 0
    elif n > 0 and k ==0:
        return 0
    else:
        return sum([f(n-i**2,k-1) for i in range(10)])

def main(N=10**7):
    power = int(log10(N))
    u = 9**2*power
    happy_numbers = [i for i in range(1,u+1) if is_happy(i)]
    ways = sum([f(x,power) for x in happy_numbers])
    return (N - ways - 1) # 严格小于 1e7 的所有数中计算

if __name__ == '__main__':
    print(main())