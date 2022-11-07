# https://en.wikipedia.org/wiki/Continued_fraction#Infinite_continued_fractions_and_convergents
# n[k]=a[k]⋅n[k−1]+n[k−2]
# https://pe.metaquant.org/pe065.html
# 直接套维基百科给的分子递推公式就行, 分母的递推公式也有但是这里用不到
# ans = 272

def main(N=100):
    nk2,nk1 = 1,2
    for i in range(2,N+1):
        a = 2 * i//3 if i%3==0 else 1
        t = nk1
        nk1 = nk2 + a * nk1
        nk2 = t
    return sum(map(int,str(nk1)))

if __name__ == '__main__':
    print(main())