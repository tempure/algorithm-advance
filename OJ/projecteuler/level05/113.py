# 112 题的加强版，本质是排列组合题
# 感觉题意有点模糊啊...
# 下降数的开头与结尾都可以是0，以及要排除掉0000题目里面也没说明吧
# https://pe.metaquant.org/pe113.html
# ans = 51161058134250

from math import factorial as fac

def comb_num(n,k):
    num = fac(n)//(fac(n-k)*fac(k))
    return num

def main(d=100):
    res = comb_num(d+9,9)+comb_num(d+10,10)-10*d-2
    return res


if __name__ == '__main__':
    print(main())