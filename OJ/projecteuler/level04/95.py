# https://pe.metaquant.org/pe095.html
# 埃氏筛思路优化一下复杂度，然后模拟即可
# ans = 14316


import numpy as np

def div_sum_dict(N=10**6):
    arr = np.zeros(N,dtype=int)
    k = 1
    for i in range(N//2):
        arr[i+k::k] += k # 注意 numpy 数组的 :: 用法不同, 从i+k开始，每隔k
        # print(i+k,k)
        k += 1
    res = {i+1:arr[i] for i in range(N)}
    # print(res)
    return res

divsum = div_sum_dict()

def amicable_chain(start):
    arr = [start]
    while True:
        n = divsum.get(start)
        if n == arr[0]:
            return arr
        elif n == 1 or n > 10**6 or n in arr:
            return None
        else:
            arr.append(n)
            start = n

def main():
    res = [amicable_chain(i) for i in range(10000,10**6)]
    return min(max([x for x in res if x!=None],key=len))

if __name__ == '__main__':
    print(main())