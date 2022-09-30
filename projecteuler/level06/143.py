# 还是一个比较难的题.....
# 从费马点几何性质利用余弦定理列出边的等式
# 本质就是转化为问题：求方程 a^2+b^2+a^b=c^2 的正整数解
# 然后接下来就是利用椭圆方程解析几何求有理数点坐标，求出点坐标之后还要求整数基本解
# 基本解当然要满足表达式中m,n的互质条件等限制条件，否则就不是基本解了
# 得到基本解之后就可以直接乘以倍数得到其他所有合法解，然后枚举保存下来所有候选项
# 此时就是求符合条件的(p,q,r)三元组了，观察到一个方程左边最多只有(p,q,r)三个中的两个
# 所以要求得一个三元组，如果一个方程左边满足 p,q 的关系，另外一个方程满足 p,r 的关系，如果此时 q,r 也能满足
# 那么这三个元素就互相牵制满足一个三元组(p,q,r)了
# 代码实现的话就是用集合的 & 求交集操作

# https://pe.metaquant.org/pe143.html
# 30758397

from math import gcd
from collections import defaultdict

def generate_pairs(N=120000):
    pairs = defaultdict(set)
    for i in range(2,346):
        for j in range(1,i):
            if gcd(i,j) == 1 and (i-j)%3 != 0:
                q,r = 2*i*j+j**2,i**2-j**2
                q,r = max(q,r),min(q,r)
            for k in range(1,N//q+1):
                pairs[k*q].add(k*r) # 基本解乘倍数地推出其他合法解
    return pairs

def main(N=120000):
    res = set()
    pairs = generate_pairs()
    for k,v in pairs.items(): # 这里需要用纸和笔模拟一下在集合中枚举查找的过程
        for q in v:
            if q in pairs:
                for r in (v & pairs[q]):
                    res.add(k+q+r)
    return sum({x for x in res if x<=N})


if __name__ == '__main__':
    print(main())