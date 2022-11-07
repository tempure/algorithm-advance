# 感觉并不是很简单...本质是佩尔方程的通解公式
# https://pe.metaquant.org/pe094.html
# 从最小的整数解开始往上一直递推，然后判断是否面积周长都是整数
# 周长是整数，那么边长 a 一定也要是整数
# ans = 518408346

def main(U=10**9):
    x,y = 7,4
    p_sum = 0
    while True:
        a1,a2 = (2*x+1)/3,(2*x-1)/3
        s1,s2 = (a1+1)*y/2,(a2-1)*y/2
        p1,p2 = (3*a1+1),(3*a2-1)
        if (p1<=U) and (a1%1==0) and (s1%1==0):
            p_sum += p1
        if (p2<=U) and (a2%1==0) and (s2%1==0):
            p_sum += p2
        if (p1>U) and (p2>U):
            return int(p_sum)
        else:
            x,y = 2*x+3*y,x+2*y


if __name__ == '__main__':
    print(main())