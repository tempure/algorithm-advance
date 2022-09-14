# https://pe.metaquant.org/pe085.html
# 推公式，确定范围枚举
# ans = 2772
"""
这题猛一看像什么蒙德里安的梦想那道经典题我还以为要深搜加上大力剪枝
根据一维的公式推广到二维还是需要思考一下正确性的，其实这个推广的C=1/2 * X * (X+1) * Y * (y+1)
就是在长和宽上任意枚举两段一维的矩形，然后他们垂直映射过来的交叉部分的矩形，就是这一对(X,Y)唯一确定的二维矩形
"""
from itertools import count

def main(N=2*10**6):
    for dist in count(1,1):
        c1,c2 = N-dist,N+dist
        limit = int(((8*c2**0.5+1)**0.5-1)/2) + 1
        for y in range(1,limit):
            t = y*(y+1)
            x1 = (-t+(t**2+16*c1*t)**0.5)/(2*t)
            x2 = (-t+(t**2+16*c2*t)**0.5)/(2*t)
            if x1.is_integer():
                return int(x1 * y)
            if x2.is_integer():
                return int(x2 * y)

if __name__ == '__main__':
    print(main())