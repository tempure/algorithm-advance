# 经典的 DICE PROBLEM
# 这题本质就是求于m个n面的骰子，其面值之和为s的可能事件总数是多少
# 小范围数据可以暴力求笛卡尔积，更优的算法是用生成函数方法：https://www.jianguoyun.com/p/DSo_XHMQ7-PvBRicz88D
# 不知道生成函数的复杂度是多少，，没仔细看 paper，但是应该比暴力笛卡尔积最少快30倍
# https://pe.metaquant.org/pe205.html
# ans = 0.5731441

# 暴力枚举法
from itertools import product
from collections import Counter

def dice_values_sum_ways(sides,number):
    arrangement = product(range(1,sides+1), repeat=number) # repeat 就是把list重复几次，然后这些list做笛卡尔积
    sum_of_values = [sum(x) for x in arrangement]
    c = Counter(sum_of_values)
    return dict(c)

def sol1():
    beats = 0
    total = (4**9) * (6**6)
    pw = dice_values_sum_ways(4,9)
    cw = dice_values_sum_ways(6,6)
    for k1,v1 in pw.items():
        for k2,v2 in cw.items():
            if k1 > k2:
                beats += (v1*v2)
    print(round(beats/total,7))


# 生成函数解法

from scipy.special import comb

def numbers_of_ways(m,n,p):
    up = int((p-m)/n)+1
    seq = [(-1)**j * comb(m,j) * comb(p-n*j-1,m-1) for j in range(up)]
    return sum(seq)

def sol2():
    beats = 0
    total = (4**9) * (6**6)
    pw = {i:numbers_of_ways(9,4,i) for i in range(9,37)}
    cw = {i:numbers_of_ways(6,6,i) for i in range(6,37)}
    for k1,v1 in pw.items():
        for k2,v2 in cw.items():
            if k1 > k2:
                beats += (v1*v2)
    return round(beats/total,7)


if __name__ == '__main__':
    sol1()