"""
https://pe.metaquant.org/pe700.html
这题本质就是一个扩展欧几里得算法
题目给的两个初始系数已经是互质的了

gcd(a,b) = gcd(b, a % b)

但是这个做法的证明可能远远没有这么简单，因为 exgcd 确实可以找到连续减小的 c 余数的合法解
但是无法证明 exgcd 每一步递推出的余数构成的集合是所有解的集合，还需要再证明必要条件才行。。。。

目前还不太会证明必要条件

ans = 1517926517777556
"""

def main():
    c = 1504170715041707
    nc = 8912517754604
    res = c + nc
    while nc > 0:
        c,nc = nc,(-c)%nc
        res += nc
    return res

if __name__ == '__main__':
    print(main())