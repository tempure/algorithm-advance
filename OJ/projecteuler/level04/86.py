# ans = 1818
# 确定范围解不等式的整数解个数
# https://pe.metaquant.org/pe086.html
# 这个题怎么就35%难度了....

def main(N=10**6):
    c,length = 0,0
    while c < N:
        length = length + 1
        for wph in range(2,2*length+1):
            sq = (length**2 + wph**2)**0.5
            if sq % 1 == 0:
                c += (wph//2) if length>wph else (length-(wph+1)//2+1)
    print(length)

if __name__ == '__main__':
    main()