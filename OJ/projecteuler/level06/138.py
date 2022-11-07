# 负佩尔方程，推公式题
# 注意判断 b 是否为整数, 以及第一组解要从题目给的样例开始，而不是方程的最小整数解，因为要构成三角形，且边长为整数
# https://pe.metaquant.org/pe138.html
# ans = 1118049290473932

def main(N=12):
    n,res = 0,0
    x,y = 38,17
    while n < N:
        b1,b2 = 2*x+4,2*x-4
        if b1%5 == 0 or b2%5==0:
            res += y
            n += 1
        x,y = 9*x+20*y,4*x+9*y
    return res


if __name__ == '__main__':
    print(main())