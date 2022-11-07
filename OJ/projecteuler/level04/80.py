# 求平方根无理数精确表示的算法
# 牛顿迭代法代码实现精度较低, 不太行
# https://pe.metaquant.org/pe080.html
# http://www.mathblog.dk/project-euler-80-digits-irrational-square-roots/
# http://www.afjarvis.staff.shef.ac.uk/maths/jarvisspec02.pdf
# ans = 40886

def jarvis_sqrt_sum(n,prec=100):
    a,b = 5*n,5
    while len(str(b)) <= prec+3:
        if a >= b:
            a,b = a-b,b+10
        else:
            a,b = a*100,(b-b%10)*10+b%10
    return sum([int(x) for x in str(b)[:prec]])

def main():
    numbers = set(range(2,100))-{x**2 for x in range(2,10)}
    ans = 0
    for i in numbers:
        ans += jarvis_sqrt_sum(i)
    print(ans)

if __name__ == '__main__':
    main()