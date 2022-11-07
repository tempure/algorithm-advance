# 杨辉三角，组合数这种题的数都是里面有阶乘存在的，且和求质因子次幂有关的，考虑勒让德公式
# https://pe.metaquant.org/pe203.html
# https://en.wikipedia.org/wiki/Legendre%27s_formula
# ans = 34029210557338

def main(n=51):
    squares = [4,9,25,49]
    res = set()
    pt = [1]
    for r in range(1,n): # 从第二行 [1,1] 开始计算n-1次
        pt = [x+y for x,y in zip(pt+[0],[0]+pt)] # 注意这里的求杨辉三角每一行的技巧，就是上一行首尾加0，然后相加
        for comb in pt:
            if all([comb%s for s in squares]) != 0:
                res.add(comb)
    return sum(res)

if __name__ == '__main__':
    print(main())
