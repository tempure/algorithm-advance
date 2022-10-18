"""
ans = 193060223
https://pe.metaquant.org/pe686.html
就直接暴力就行了，考虑大整数计算，因为只关心前3位，所以超过1000可以直接除
这个相当于你最后乘完了再除以一个 10^(len-3)，和边乘边除是等价的
"""

from numba import njit

@njit

def main(target = 123, N = 678910):
    n, power, k = 0, 2, 1
    while n < N:
        power = power * 2
        while power >= 10**3:
            power = power / 10.0
        if int(power) == target:
            n = n + 1
        k = k + 1
    return k


if __name__ == '__main__':
    print(main())