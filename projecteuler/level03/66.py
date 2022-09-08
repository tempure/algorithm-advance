# 根据 https://pe.metaquant.org/pe064.html 三项递推关系
# 根据 https://pe.metaquant.org/pe065.html 求渐进表示的分子分母
# 根据 https://pe.metaquant.org/pe066.html 求佩尔方程的解
# ans: D = 661
def pell_equation(D):
    a0 = int(D**0.5)
    a1 = int(2*a0/(D-a0**2))
    seq,P,Q = [a0,a1],[a0,a1*a0+1],[1,a1]
    m,d = a0,D-a0**2
    while seq[-1] != 2*a0:
        m = d*seq[-1]-m
        d = (D-m**2)//d
        seq.append(int((a0+m)/d))
        P.append(seq[-1]*P[-1]+P[-2])
        Q.append(seq[-1]*Q[-1]+Q[-2])
    if (len(seq)-1) % 2 == 0:
        return (P[-2],Q[-2])
    else:
        return (P[-2]**2+Q[-2]**2*D,2*P[-2]*Q[-2])

def main(N=1000):
    dt = {}
    for i in range(2,N+1):
        if int(i**0.5)**2 == i:
            continue
        else:
            dt[i] = pell_equation(i)[0]
    return max(dt,key=dt.get)

if __name__ == '__main__':
    print(main())