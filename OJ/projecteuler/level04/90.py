# 枚举所有排列组合然后判断就行
# 技巧就是注意提前把所有9都换成6方便比较集合
# 注意关注的是立方体上有哪些数字，而不关心它们填在哪些面上
# 交换两个立方体的结果一样，最后要除以2
# ans = 1217

from itertools import combinations

def main():
    counter = 0
    sq = {1,4,6,16,25,36,46,64,81}
    cube_number = list(range(9)) + [6]
    comb = list(combinations(cube_number,6)) # 给出C(10,6)种排列的二维list
    # print(comb)
    for i in comb:
        for j in comb:
            numbers = {e for x in i for y in j for e in (10*x+y,10*y+x)}
            if sq <= numbers:
                counter += 1
    return counter//2

if __name__ == '__main__':
    print(main())