"""
几何题，基本思路就是想办法求两个圆心的坐标
需要用到的有求内心坐标公式，以及笛卡尔定理求和三个圆相切的第四个圆的坐标

https://en.wikipedia.org/wiki/Incenter#Cartesian_coordinates
https://en.wikipedia.org/wiki/Descartes%27_theorem
https://pe.metaquant.org/pe727.html

注释中所有圆位置按照题解后面的图看，c在上，a，b在下

ans = 3.64039141 注意题目要求四舍五入
"""

from math import sqrt,gcd
from itertools import combinations
from functools import reduce

def cods(a,b,r): # 已知圆c和圆a,b相切，知道ra，ra，rc以及a，b的圆心坐标，求c的圆心坐标
    x = ((a+b)**2+(r+a)**2-(r+b)**2)/(2*a+2*b)
    y = sqrt((a+r)**2-x**2)
    return x,y

def inner_point(a,b,c): # 求圆心坐标
    xa,ya = 0,0
    xb,yb = a+b,0
    xc,yc = cods(a,b,c)
    x = ((b+c)*xa+(a+c)*xb+(a+b)*xc)/(2*(a+b+c))
    y = ((b+c)*ya+(a+c)*yb+(a+b)*yc)/(2*(a+b+c))
    return x,y

def soddy_circle_radius(a,b,c): # 笛卡尔定理求小圆半径
    return (a*b*c)/(a*b+a*c+b*c+2*sqrt(a*b*c*(a+b+c)))

def dist(a,b,c):
    xd,yd = inner_point(a,b,c)
    # 圆c和圆a,b是相切的，小圆也和a,b是相切的
    xe,ye = cods(a,b,soddy_circle_radius(a,b,c))
    return sqrt((xd-xe)**2+(yd-ye)**2)

def ggcd(numbers):
    return reduce(gcd,numbers)

def main():
    res = [x for x in combinations(range(1,101),3) if ggcd(x)==1]
    return sum(dist(*x) for x in res)/len(res)

if __name__ == '__main__':
    print(main())

