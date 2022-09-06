# https://pe.metaquant.org/pe056.html
# 暴力
# ans = 972

def main():
    str_sum = lambda y : sum([int(x) for x in str(y)])
    res = max([str_sum(a**b) for a in range(1,100) for b in range(1,100)])
    return res

if __name__ == '__main__':
    print(main())