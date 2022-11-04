# ans = 20313839404245
# 题目给的那个错误的构造法，对于本题恰好是对的
# brute force solution: https://www.mathblog.dk/project-euler-103-special-subset-sum/
# https://pe.metaquant.org/pe103.html 给出了最优解的寻找思路，但是没有说明原因...
# PE 论坛看了一圈也是不知所云... 假题丁真，鉴定为：申必题

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

def main(arr=[11,18,19,20,22,25],n=7):
    optimum = set(arr[len(arr)//2:] + sorted([x+y for x in arr for y in arr]))
    for i in combinations(optimum,n):
        if is_special_sumsets(i):
            return "".join([str(x) for x in i])


if __name__ == '__main__':
    print(main())