# 和 103 题一样的
# 直接拿过来枚举检验一遍就行了
# ans = 73702


from itertools import combinations

def is_valid(B,tup):
    L,S = tup
    if len(B) == L:
        return sum(B) != S
    else:
        return (sum(B)-S)*(len(B)-L)>0

def is_special_sumsets(s):
    arr = [(1,x) for x in sorted(s)]
    for r in range(2,len(s)):
        for i in combinations(sorted(s),r):
            for j in arr:
                if not is_valid(i,j):
                    return False
            arr.append((len(i),sum(i)))
    return True

def main():
    res = 0
    with open('../data/p105_sets.txt') as f:
        sets = [[int(x) for x in row.strip().split(',')] for row in f.readlines()]
    for s in sets:
        if is_special_sumsets(s):
            res += sum(s)
    return res


if __name__ == '__main__':
    print(main())