# 推公式题，解不等式得到范围之后然后暴力枚举就行了。。
# https://pe.metaquant.org/pe135.html
# ans = 4989
# 这题居然有 45% 难度。。。

from collections import defaultdict

def main(N=10**6):
    res = defaultdict(int)
    for a in range(2,N+1):
        u = min(a,(N+a**2)//(4*a)+1)
        for d in range(a//4+1,u):
            res[a*(4*d-a)] += 1
    return len([k for k,v in res.items() if v==10])

if __name__ == '__main__':
    print(main())