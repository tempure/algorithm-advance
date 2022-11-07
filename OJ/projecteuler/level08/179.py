# https://github.com/RobertoGuzmanJr/ProjectEuler/blob/master/Problem_179.cs
# 这个题就很简单的埃氏筛思路筛的同时记录一下就行了....
# 也可以按照：https://pe.metaquant.org/pe179.html 的思路更加优化但是好像快不了多少
# ans = 986262

import numpy as np
# from numba import njit

def main_slow():
    res = 0
    max = 10**7
    cnt = [0]*(max)
    for i in range(2, max): # 注意题目范围 n < 1e7
        cnt[i]+=1
        for j in range(i, max, i):
            cnt[j]+=1
        if cnt[i] == cnt[i-1]:
            res+=1
    print(res)
    # print(cnt)



# @njit
def number_of_divisors(N):
    nod = np.array([0,1]+[2]*(N-1))
    u = int(N**0.5)
    for i in range(2,u+1):
        nod[i*i] += 1
        for j in range(i+1,N//i+1):
            nod[i*j] += 2
    return nod

def main(N=10**7):
    nod = number_of_divisors(N)
    diff = np.diff(nod)
    res = N - np.count_nonzero(diff)
    print(res)
    # print(nod)

if __name__ == '__main__':
    main_slow()
    main()