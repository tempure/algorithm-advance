"""
https://pe.metaquant.org/pe243.html
这个题也不是很简单, 第一眼能看出来是欧拉函数，但是后面推导的思路就非常跳跃了
注意题解里面后面的应该是 p|d, 而不是p|n
a/b 是个真分数，就题解里面写的要找的是最少的素数连乘积，这个结论我觉得需要证明，不是显然的
因为式子里面是 d/(d-1)*PI(p-1)/PI(p) < a/b, 首先 a/b 是个真分数，对于递增的 p, 每次都是给左边的式子乘一个
(p-1)/p, 这是个真分数，所以相当于左边在一直减小，第一个小于 a/b 的就是符合的。

然后d=ky这一步的转换也挺跳跃的，但是这个转换你不换也能求，因为本质还是求最小连续素数乘积满足就行了
估计是为了代码实现更加容易

ans = 892371480
"""
from sympy import prime
from fractions import Fraction as f
from math import prod

def main(a=15499,b=94744):
    fy = lambda n:prod([prime(i) for i in range(1,n+1)])
    fx = lambda n:prod([prime(i)-1 for i in range(1,n+1)])
    n = 1
    while True:
        if f(fy(n),fx(n)) > f(b,a):
            break
        n = n + 1
    k = int(a/(a*fy(n)-b*fx(n)))+1
    return k * fy(n)


if __name__ == '__main__':
    print(main())