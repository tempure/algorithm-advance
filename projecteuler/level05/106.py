# 这题看起来像 103, 105 其实不是一回事
# 题目给定初始序列是有序的，然后自习想一下本质就是求卡特兰数
# 符合卡特兰数的序列就是不用检验的
# https://pe.metaquant.org/pe106.html
# ans = 21384

from math import factorial as fac

def comb_num(n,k):
    num = fac(n)//(fac(n-k)*fac(k))
    return num

def main(N=12):
    res = 0
    for i in range(1,N//2+1):
        res += comb_num(N,2*i)*(comb_num(2*i,i)//2-comb_num(2*i,i)//(i+1))
    return res


if __name__ == '__main__':
    print(main())