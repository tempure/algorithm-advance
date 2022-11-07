# 计算几何入门题
# https://pe.metaquant.org/pe102.html
# 求三角形面积的一些方法：https://zhuanlan.zhihu.com/p/25793392
# 注意面积法应该和3个点坐标的顺序无关，题目给的数据横坐标都不一定是单调的, 但是我懒得证了
# ans = 228

def area_of_triangle(xa,ya,xb,yb,xc,yc):
    area = abs((xa-xc)*(yb-ya)-(xa-xb)*(yc-ya)) / 2
    return area

def main():
    counter = 0
    with open('../data/p102_triangles.txt') as f:
        coords = [x.strip().split(',') for x in f.readlines()]
        for coord in coords:
            xa,ya,xb,yb,xc,yc = [int(x) for x in coord]
            abc = area_of_triangle(xa,ya,xb,yb,xc,yc)
            aob = area_of_triangle(xa,ya,0,0,xb,yb)
            aoc = area_of_triangle(xa,ya,0,0,xc,yc)
            boc = area_of_triangle(xb,yb,0,0,xc,yc)
            if abc == aob + aoc + boc:
                counter += 1
    return counter

if __name__ == '__main__':
    print(main())