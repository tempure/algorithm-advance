# 负佩尔方程(negative Pell equation)
# 推公式然后递推即可
# https://pe.metaquant.org/pe100.html
# ans = 756872327473


def main(N=10**12):
    b,t = 15,21
    while t < N:
        b,t = 2*t+3*b-2,3*t+4*b-3
    return b

if __name__ == '__main__':
    print(main())