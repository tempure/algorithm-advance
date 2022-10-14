"""
题目背景就是笛卡尔定理的特殊情况: https://en.wikipedia.org/wiki/Descartes%27_theorem#Special_cases
满足题目要求的情况下的 Ra, Rb, Rc 符合特殊情况的公式
https://pe.metaquant.org/pe510.html

思路比较跳跃的一点是设解的格式: Ra = k*u^2, Rb = k*v^2, 且满足 gcd(u,v) = 1
代码实现上来看就是枚举u,v 那么保证 gcd(u,v)=1 是为了不重复计数，当k=1的时候是最小的基本解

因为你u,v不互质的话那肯定除gcd(u,v)得到一组更小的解，此时的系数k肯定就重复了

ans = 315306518862563689

一个问题：为什么一定要把  ra, rb 设为ku^2, kv^2 的原理什么，是否意味着 ra，rb 一定是某个整数的平方的k倍才能成立？
如果不设为ku^2, kv^2, 那么 rc 还能为整数吗？

就从最简单的 k = 1 情况来看，这里的意思就是 ra, rb 都是简单的整数的平方
如果不是整数的平方，那么是否 rc 还有可能为整数？
"""

from math import gcd

def triplets(u,v):
    rc = (u*v)**2
    ra = ((u+v)*u)**2
    rb = ((u+v)*v)**2
    return rc,ra,rb

def main(n=10**9):
    res = 0
    u = int(((1+4*n**0.5)**0.5-1)/2)
    for j in range(1,u+1):
        for i in range(1,j+1):
            k = 1
            if gcd(i,j) == 1:
                rc,ra,rb = triplets(i,j)
                k = n // rb
                res += k*(k+1)*(rc+ra+rb)//2
    return res

if __name__ == '__main__':
    print(main())