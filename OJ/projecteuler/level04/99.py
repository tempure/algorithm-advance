# 取对数比较即可
# https://pe.metaquant.org/pe099.html
# 直接暴力算很慢
# ans = 709

from math import log10

def main():
    with open('../data/p099_base_exp.txt') as f:
        pairs = [list(map(int,s.split(','))) for s in f.readlines()]
    log_pairs = [x[1]*log10(x[0]) for x in pairs]
    return log_pairs.index(max(log_pairs))+1

if __name__ == '__main__':
    print(main())